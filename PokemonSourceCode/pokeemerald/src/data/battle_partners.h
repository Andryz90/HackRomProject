//
// DO NOT MODIFY THIS FILE! It is auto-generated from src/data/battle_partners.party
//
// If you want to modify this file set COMPETITIVE_PARTY_SYNTAX to FALSE
// in include/config/general.h and remove this notice.
// Use sed -i '/^#line/d' 'src/data/battle_partners.h' to remove #line markers.
//

#line 1 "src/data/battle_partners.party"

#line 1
    [PARTNER_NONE] =
    {
#line 3
        .trainerClass = TRAINER_CLASS_PKMN_TRAINER_1,
#line 4
        .trainerPic = TRAINER_BACK_PIC_BRENDAN,
        .encounterMusic_gender = 
#line 6
            TRAINER_ENCOUNTER_MUSIC_MALE,
        .partySize = 0,
        .party = (const struct TrainerMon[])
        {
        },
    },
#line 8
    [PARTNER_WALLY] =
    {
#line 9
        .trainerName = _("WALLY"),
#line 10
        .trainerClass = TRAINER_CLASS_RIVAL,
#line 11
        .trainerPic = TRAINER_BACK_PIC_WALLY,
        .encounterMusic_gender = 
#line 13
            TRAINER_ENCOUNTER_MUSIC_MALE,
        .partySize = 3,
        .party = (const struct TrainerMon[])
        {
            {
#line 15
            .species = SPECIES_KIRLIA,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 15
            .heldItem = ITEM_SITRUS_BERRY,
#line 19
            .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
#line 16
            .ability = ABILITY_TRACE,
#line 17
            .lvl = 22,
#line 18
            .nature = NATURE_BOLD,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 20
                MOVE_PSYBEAM,
                MOVE_LIFE_DEW,
                MOVE_DRAINING_KISS,
            },
            },
            {
#line 24
            .species = SPECIES_AZUMARILL,
#line 24
            .gender = TRAINER_MON_MALE,
#line 28
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 25
            .ability = ABILITY_HUGE_POWER,
#line 26
            .lvl = 21,
#line 27
            .nature = NATURE_ADAMANT,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 28
                MOVE_HELPING_HAND,
                MOVE_AQUA_TAIL,
                MOVE_BOUNCE,
                MOVE_CHARM,
            },
            },
            {
#line 33
            .species = SPECIES_DEDENNE,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 33
            .heldItem = ITEM_ORAN_BERRY,
#line 36
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 34
            .ability = ABILITY_CHEEK_POUCH,
#line 35
            .lvl = 21,
            .nature = NATURE_HARDY,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 36
                MOVE_NUZZLE,
                MOVE_DRAINING_KISS,
                MOVE_THUNDER_SHOCK,
            },
            },
        },
    },
#line 40
    [PARTNER_STEVEN] =
    {
#line 41
        .trainerName = _("STEVEN"),
#line 42
        .trainerClass = TRAINER_CLASS_RIVAL,
#line 43
        .trainerPic = TRAINER_BACK_PIC_STEVEN,
        .encounterMusic_gender = 
#line 45
            TRAINER_ENCOUNTER_MUSIC_MALE,
        .partySize = 3,
        .party = (const struct TrainerMon[])
        {
            {
#line 47
            .species = SPECIES_METANG,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 51
            .ev = TRAINER_PARTY_EVS(0, 252, 252, 0, 6, 0),
#line 50
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 49
            .lvl = 42,
#line 48
            .nature = NATURE_BRAVE,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 52
                MOVE_LIGHT_SCREEN,
                MOVE_PSYCHIC,
                MOVE_REFLECT,
                MOVE_METAL_CLAW,
            },
            },
            {
#line 57
            .species = SPECIES_SKARMORY,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 61
            .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 6, 252),
#line 60
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 59
            .lvl = 43,
#line 58
            .nature = NATURE_IMPISH,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 62
                MOVE_TOXIC,
                MOVE_AERIAL_ACE,
                MOVE_PROTECT,
                MOVE_STEEL_WING,
            },
            },
            {
#line 67
            .species = SPECIES_AGGRON,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 71
            .ev = TRAINER_PARTY_EVS(0, 252, 0, 0, 252, 6),
#line 70
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 69
            .lvl = 44,
#line 68
            .nature = NATURE_ADAMANT,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 72
                MOVE_THUNDER,
                MOVE_PROTECT,
                MOVE_SOLAR_BEAM,
                MOVE_DRAGON_CLAW,
            },
            },
        },
    },
