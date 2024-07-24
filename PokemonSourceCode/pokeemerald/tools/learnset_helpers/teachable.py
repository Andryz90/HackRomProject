import glob
import re
import json
import os

# before all else, abort if the config is off
with open("./include/config/pokemon.h", "r") as file:
    learnset_config = re.findall(r"#define P_LEARNSET_HELPER_TEACHABLE *([^ ]*)", file.read())
    if len(learnset_config) != 1:
        quit()
    if learnset_config[0] != "TRUE":
        quit()

def parse_mon_name(name):
    return re.sub(r'(?!^)([A-Z]+)', r'_\1', name).upper()
    
tm_moves = []
tutor_moves = []
level_for_moves = {}
# scan incs
incs_to_check =  glob.glob('./data/scripts/*.inc') # all .incs in the script folder
incs_to_check += glob.glob('./data/maps/*/scripts.inc') # all map scripts

if len(incs_to_check) == 0: # disabled if no jsons present
    quit()

for file in incs_to_check:
    with open(file, 'r', encoding="utf8") as f2:
        raw = f2.read()
    if 'special ChooseMonForMoveTutor' in raw:
        for x in re.findall(r'setvar VAR_0x8005, (MOVE_.*)', raw):
            if not x in tutor_moves:
                tutor_moves.append(x)

# scan TMs and HMs
with open("./include/constants/tms_hms.h", 'r') as file:
    for x in re.findall(r'F\((.*)\)', file.read()):
        if not 'MOVE_' + x in tm_moves:
            tm_moves.append('MOVE_' + x)

# look up universal moves to exclude them
universal_moves = []
with open("./src/pokemon.c", "r") as file:
    for x in re.findall(r"static const u16 sUniversalMoves\[\] =(.|\n)*?{((.|\n)*?)};", file.read())[0]:
        x = x.replace("\n", "")
        for y in x.split(","):
            y = y.strip()
            if y == "":
                continue

# get compatibility from jsons
def construct_compatibility_dict(force_custom_check):
    dict_out = {}
    for pth in glob.glob('./tools/learnset_helpers/porymoves_files/*.json'):
        f = open(pth, 'r')
        if pth != './tools/learnset_helpers/porymoves_files\\custom.json':
            data = json.load(f)
            for mon in data.keys():
                if not mon in dict_out:
                    dict_out[mon] = []

                #for move in data[mon]['PreEvoMoves']:
                #    if not move in dict_out[mon]:
                #        dict_out[mon].append(move)
                for move in data[mon]['TMMoves']:
                    if not move in dict_out[mon]:
                        dict_out[mon].append(move)
                for move in data[mon]['EggMoves']:
                    if not move in dict_out[mon]:
                        dict_out[mon].append(move)
                for move in data[mon]['TutorMoves']:
                    if not move in dict_out[mon]:
                        dict_out[mon].append(move)
        else:
            for mon in data.keys():
                if not mon in dict_out:
                    dict_out[mon] = []
                    level_for_moves[mon] = []
                universal_moves.append(y)
                for move in data[mon]['TMMoves']:
                    if not move in dict_out[mon]:
                        dict_out[mon].append(move['Move'])
                for move in data[mon]['EggMoves']:
                    if not move in dict_out[mon]:
                        dict_out[mon].append(move)
                for move in data[mon]['TutorMoves']:
                    if not move in dict_out[mon]:
                        dict_out[mon].append(move)        

    # if the file was not previously generated, check if there is custom data there that needs to be preserved
    with open("./src/data/pokemon/teachable_learnsets.h", 'r') as file:
        raw = file.read()
        if not "// DO NOT MODIFY THIS FILE!" in raw and force_custom_check == True:
            custom_teachable_compatibilities = {}
            for entry in re.findall(r"static const u16 s(.*)TeachableLearnset\[\] = {\n((.|\n)*?)\n};", raw):
                monname = parse_mon_name(entry[0])
                if monname == "NONE":
                    continue
                compatibility = entry[1].split("\n")
                if not monname in custom_teachable_compatibilities:
                    custom_teachable_compatibilities[monname] = []
                if not monname in dict_out:
                    # this mon is unknown, so all data needs to be preserved
                    for move in compatibility:
                        move = move.replace(",", "").strip()
                        if move == "" or move == "MOVE_UNAVAILABLE":
                            continue
                        custom_teachable_compatibilities[monname].append(move)
                else:
                    # this mon is known, so check if the moves in the old teachable_learnsets.h are not in the jsons
                    for move in compatibility:
                        move = move.replace(",", "").strip()
                        if move == "" or move == "MOVE_UNAVAILABLE":
                            continue
                        if not move in dict_out[monname]:
                            custom_teachable_compatibilities[monname].append(move)
            # actually store the data in custom.json
            if os.path.exists("./tools/learnset_helpers/porymoves_files/custom.json"):
                f2 = open("./tools/learnset_helpers/porymoves_files/custom.json", "r")
                custom_json = json.load(f2)
                f2.close()
            else:
                custom_json = {}
            for x in custom_teachable_compatibilities:
                if len(custom_teachable_compatibilities[x]) == 0:
                    continue
                if not x in custom_json:
                    custom_json[x] = { "LevelMoves": [], "PreEvoMoves": [], "TMMoves": [], "EggMoves": [], "TutorMoves": []}
                for move in custom_teachable_compatibilities[x]:
                    custom_json[x]["TutorMoves"].append(move)
                f2 = open("./tools/learnset_helpers/porymoves_files/custom.json", "w")
                f2.write(json.dumps(custom_json, indent=2))
                f2.close()
            print("FIRST RUN: Updated custom.json with teachable_learnsets.h's data")
            # rerun the process
            dict_out = construct_compatibility_dict(False)
    return dict_out

compatibility_dict = construct_compatibility_dict(True)

# actually prepare the file
with open("./src/data/pokemon/teachable_learnsets.h", 'r') as file:
    out = file.read()
    list_of_mons = re.findall(r'static const u16 s(.*)TeachableLearnset', out)
for mon in list_of_mons:
    mon_parsed = parse_mon_name(mon)
    tm_learnset = []
    tutor_learnset = []
    if mon_parsed == "NONE" or mon_parsed == "MEW":
        continue
    if not mon_parsed in compatibility_dict:
        print("Unable to find %s in json" % mon)
        continue
    
    for move in compatibility_dict[mon_parsed]:
        if move in tutor_moves:
            continue
        if move in tm_learnset:
            continue
        if move in universal_moves:
            continue
        tm_learnset.append(move)

    # for move in tm_moves:
    #     if move in universal_moves:
    #         continue
    #     if move in tm_learnset:
    #         continue
    #     if move in compatibility_dict[mon_parsed]:
    #         tm_learnset.append(move)
    #         continue
        
    for move in tutor_moves:
        if move in universal_moves:
            continue
        if move in tutor_learnset:
            continue
        if move in compatibility_dict[mon_parsed]:
            tutor_learnset.append(move)
            continue
    tm_learnset.sort()
    tutor_learnset.sort()
    tm_learnset += tutor_learnset
    repl = "static const u16 s%sTeachableLearnset[] = {\n    " % mon
    if len(tm_learnset) > 0:
        repl += ",\n    ".join(tm_learnset) + ",\n    "
    repl += "MOVE_UNAVAILABLE,\n};"
    newout = re.sub(r'static const u16 s%sTeachableLearnset\[\] = {[\s\S]*?};' % mon, repl, out)
    if newout != out:
        out = newout
        print("Updated %s" % mon)

# add/update header
header = "//\n// DO NOT MODIFY THIS FILE! It is auto-generated from tools/learnset_helpers/teachable.py\n//\n\n"
longest_move_name = 0
for move in tm_moves + tutor_moves:
    if len(move) > longest_move_name:
        longest_move_name = len(move)
longest_move_name += 2 # + 2 for a hyphen and a space

universal_title = "Near-universal moves found in sUniversalMoves:"
tmhm_title = "TM/HM moves found in \"include/constants/tms_hms.h\":"
tutor_title = "Tutor moves found in map scripts:"

if longest_move_name < len(universal_title):
    longest_move_name = len(universal_title)
if longest_move_name < len(tmhm_title):
    longest_move_name = len(tmhm_title)
if longest_move_name < len(tutor_title):
    longest_move_name = len(tutor_title)

def header_print(str):
    global header
    header += "// " + str + " " * (longest_move_name - len(str)) + " //\n"

header += "// " + longest_move_name * "*" + " //\n"
header_print(tmhm_title)
for move in tm_moves:
    header_print("- " + move)
header += "// " + longest_move_name * "*" + " //\n"
header_print(tutor_title)
tutor_moves.sort() # alphabetically sort tutor moves for easier referencing
for move in tutor_moves: 
    header_print("- " + move)
header += "// " + longest_move_name * "*" + " //\n"
header_print(universal_title)
universal_moves.sort() # alphabetically sort near-universal moves for easier referencing
for move in universal_moves:
    header_print("- " + move)
header += "// " + longest_move_name * "*" + " //\n\n"

if not "// DO NOT MODIFY THIS FILE!" in out:
    out = header + out
else:
    out = re.sub(r"\/\/\n\/\/ DO NOT MODIFY THIS FILE!(.|\n)*\* \/\/\n\n", header, out)

with open("./src/data/pokemon/teachable_learnsets.h", 'w') as file:
    file.write(out)


#Same thing but for Level up Moves
# get compatibility from jsons


def construct_compatibility_levelset(force_custom_check):
    dict_out = {}
    json_gen_string = ''
    done = False
    for pth in glob.glob('./tools/learnset_helpers/porymoves_files/Gen9/*.json'):
        f = open(pth, 'r')
        data = json.load(f)
        if pth != './tools/learnset_helpers/porymoves_files/Gen9/\\custom.json':
            for mon in data.keys():
                if not mon in dict_out:
                    dict_out[mon] = []
                    level_for_moves[mon] = []
                if len(data[mon]['LevelMoves']) != 0:
                    for move in data[mon]['LevelMoves']:
                        if not move['Move'] in dict_out[mon]:
                            dict_out[mon].append(move['Move'])
                            level_for_moves[mon].append(move['Level'])
                else:
                    
                    for i in reversed(range(1,9)):
                        if done:
                            done = False
                            break
                        json_gen_string = './tools/learnset_helpers/porymoves_files/Gen' + str(i)+'/*.json'
                        for pth in  glob.glob(json_gen_string):
                            f = open(pth, 'r')
                            data_new = json.load(f)
                            if mon in data_new.keys() and len(data_new[mon]['LevelMoves']) != 0 :
                                for move in data_new[mon]['LevelMoves']:
                                    if not move['Move'] in dict_out[mon]:
                                        dict_out[mon].append(move['Move'])
                                        level_for_moves[mon].append(move['Level'])
                                        done = True
                            else:
                                continue             
                        
        else:
            for mon in data.keys():
                if not mon in dict_out:
                    dict_out[mon] = []
                    level_for_moves[mon] = []
                for move in data[mon]['LevelMoves']:
                    if not move['Move'] in dict_out[mon]:
                        dict_out[mon].append(move['Move'])
                        level_for_moves[mon].append(move['Level'])
        

            

    # if the file was not previously generated, check if there is custom data there that needs to be preserved
    with open("./src/data/pokemon/level_up_learnsets/gen_9.h", 'r') as file:
        raw = file.read()
        if  force_custom_check == True:
            custom_teachable_compatibilities = {}
            level = []
            for entry in re.findall(r"static const struct LevelUpMove s(.*)LevelUpLearnset\[\] = {\n((.|\n)*?)\n};", raw):
                monname = parse_mon_name(entry[0])
                if monname == "NONE":
                    continue
                compatibility = entry[1].split("\n")
                if not monname in custom_teachable_compatibilities:
                    custom_teachable_compatibilities[monname] = { 'Moves':[], 'Level':[]}
                if not monname in dict_out:
                    # this mon is unknown, so all data needs to be preserved
                    for move in compatibility:
                        move = move.strip()
                        if (move != 'LEVEL_UP_END' and len(move) > 0):
                            level = move[move.index('(')+1:move.index(',')]
                            level = level.strip()
                            move = move[move.index(',')+2:move.index(')')]
                        move = move.replace(",", "").strip()
                        if move == "" or move == "MOVE_UNAVAILABLE":
                            continue
                        custom_teachable_compatibilities[monname]["Moves"].append(move)
                        custom_teachable_compatibilities[monname]["Level"].append(level)
                else:
                    # this mon is known, so check if the moves in the old teachable_learnsets.h are not in the jsons
                    for move in compatibility: 
                        move = move.strip()
                        if (move != 'LEVEL_UP_END' and len(move) > 0):
                            level = move[move.index('(')+1:move.index(',')]
                            level = level.strip()
                            move = move[move.index(',')+2:move.index(')')]
                            # move = move.replace(",", "").strip()
                            if move == "" or move == "MOVE_UNAVAILABLE":
                                continue
                            if not move in dict_out[monname]:
                                custom_teachable_compatibilities[monname]["Moves"].append(move)
                                custom_teachable_compatibilities[monname]["Level"].append(int(level))
                            
            # actually store the data in custom.json
            if os.path.exists("./tools/learnset_helpers/porymoves_files/Gen9/custom.json"):
                f2 = open("./tools/learnset_helpers/porymoves_files/Gen9/custom.json", "r")
                custom_json = json.load(f2)
                f2.close()
            else:
                custom_json = {}
            for x in custom_teachable_compatibilities:
                if len(custom_teachable_compatibilities[x]) == 0:
                    continue
                if not x in custom_json:
                    custom_json[x] = { "LevelMoves": []}
                index = 0
                for move in custom_teachable_compatibilities[x]["Moves"]:
                    custom_json[x]["LevelMoves"].append({"Move":move, 'Level':custom_teachable_compatibilities[x]["Level"][index]})
                    index+=1       
                f2 = open("./tools/learnset_helpers/porymoves_files/Gen9/custom.json", "w")
                f2.write(json.dumps(custom_json, indent=2))
                f2.close()
            print("FIRST RUN: Updated custom.json with Gen9_Learnset.h's data")
            # rerun the process
            dict_out = construct_compatibility_levelset(False)
    return dict_out

compatibility_dict = construct_compatibility_levelset(True)
# actually prepare the file
with open("./src/data/pokemon/level_up_learnsets/gen_9.h", 'r') as file:
    out = file.read()
    list_of_mons = re.findall(r'static const struct LevelUpMove s(.*)LevelUpLearnset', out)
for mon in list_of_mons:
    mon_parsed = parse_mon_name(mon)
    levelup_moves = []
    levels = []
    index = 0
    index_lenght = 0
    if mon_parsed == "NONE":
        continue
    if not mon_parsed in compatibility_dict:
        print("Unable to find %s in json" % mon)
        continue
    
    for move in compatibility_dict[mon_parsed]:
        levelup_moves.append(move)
        levels.append(level_for_moves[mon_parsed][index])
        index += 1
    #levelup_moves.sort()
    repl = "static const struct LevelUpMove s%sLevelUpLearnset[] = {\n    " % mon
    index = 0
    index_lenght = len(levelup_moves)
    while index < index_lenght :
        if len(levelup_moves) > 0:
            repl += "    LEVEL_UP_MOVE("+(str(levels[index]))+", "+(levelup_moves[index]) + "),\n    "
        index += 1
    repl += "    LEVEL_UP_END\n};"
    newout = re.sub(r'static const struct LevelUpMove s%sLevelUpLearnset\[\] = {[\s\S]*?};' % mon, repl, out)
    if newout != out:
        out = newout
        print("Updated %s" % mon)
        
# add/update header
header = "//\n// DO NOT MODIFY THIS FILE! It is auto-generated from tools/learnset_helpers/teachable.py\n//\n\n"
if not "// DO NOT MODIFY THIS FILE!" in out:
    out = header + out
else:
    out = re.sub(r"\/\/\n\/\/ DO NOT MODIFY THIS FILE!(.|\n)*\* \/\/\n\n", header, out)

with open("./src/data/pokemon/level_up_learnsets/gen_9.h", 'w') as file:
    file.write(out)