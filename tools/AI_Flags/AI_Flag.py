f = open("trainers_party.txt", "r")
r = open("trainers_party_edited.txt", "a")
content = f.readlines()
for ln in content:
    if ln.startswith("AI: Check bad Move/ Try To Faint/ Prefer Strongest Move/ Check Viability/ HP Aware/ Smart Switching/ Smart Mon Choices / Omniscient"):
        r.write(ln)
    elif ln.startswith("AI:"):
        ln = "AI: Check bad Move/ Try To Faint/ Prefer Strongest Move/ Check Viability/ HP Aware/ Smart Switching/ Smart Mon Choices\n"
        r.write(ln)
    elif not ln.strip("\n").startswith("Tera Type: "):
        r.write(ln)
r.close()
f.close()
