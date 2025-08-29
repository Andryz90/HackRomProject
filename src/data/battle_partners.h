//
// DO NOT MODIFY THIS FILE! It is auto-generated from src/data/battle_partners.party
//
// If you want to modify this file set COMPETITIVE_PARTY_SYNTAX to FALSE
// in include/config/general.h and remove this notice.
// Use sed -i '/^#line/d' 'src/data/battle_partners.h' to remove #line markers.
//

#line 1 "src/data/battle_partners.party"

#line 1
    [DIFFICULTY_NORMAL][PARTNER_NONE] =
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
    [DIFFICULTY_NORMAL][PARTNER_WALLY] =
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
#line 41
    [DIFFICULTY_NORMAL][PARTNER_WALLY_DESERT] =
    {
#line 42
        .trainerName = _("WALLY"),
#line 43
        .trainerClass = TRAINER_CLASS_RIVAL,
#line 44
        .trainerPic = TRAINER_BACK_PIC_WALLY,
        .encounterMusic_gender =
#line 46
            TRAINER_ENCOUNTER_MUSIC_MALE,
        .partySize = 3,
        .party = (const struct TrainerMon[])
        {
            {
#line 48
            .species = SPECIES_GARDEVOIR,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 48
            .heldItem = ITEM_LIFE_ORB,
#line 52
            .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
#line 49
            .ability = ABILITY_TRACE,
#line 50
            .lvl = 45,
#line 51
            .nature = NATURE_TIMID,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 53
                MOVE_MOONBLAST,
                MOVE_PSYCHIC_NOISE,
                MOVE_ENERGY_BALL,
                MOVE_CALM_MIND,
            },
            },
            {
#line 58
            .species = SPECIES_GALLADE,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 58
            .heldItem = ITEM_EXPERT_BELT,
#line 62
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 59
            .ability = ABILITY_SHARPNESS,
#line 60
            .lvl = 45,
#line 61
            .nature = NATURE_JOLLY,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 62
                MOVE_PSYCHO_CUT,
                MOVE_NIGHT_SLASH,
                MOVE_DRAIN_PUNCH,
                MOVE_ICE_PUNCH,
            },
            },
            {
#line 67
            .species = SPECIES_TINKATON,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 67
            .heldItem = ITEM_AIR_BALLOON,
#line 71
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 68
            .ability = ABILITY_MOLD_BREAKER,
#line 69
            .lvl = 45,
#line 70
            .nature = NATURE_ADAMANT,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 71
                MOVE_PROTECT,
                MOVE_FAKE_OUT,
                MOVE_GIGATON_HAMMER,
                MOVE_PLAY_ROUGH,
            },
            },
        },
    },
#line 77
    [DIFFICULTY_NORMAL][PARTNER_STEVEN] =
    {
#line 78
        .trainerName = _("STEVEN"),
#line 79
        .trainerClass = TRAINER_CLASS_RIVAL,
#line 80
        .trainerPic = TRAINER_BACK_PIC_STEVEN,
        .encounterMusic_gender =
#line 82
            TRAINER_ENCOUNTER_MUSIC_MALE,
        .partySize = 3,
        .party = (const struct TrainerMon[])
        {
            {
#line 84
            .species = SPECIES_METANG,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 88
            .ev = TRAINER_PARTY_EVS(0, 252, 252, 0, 6, 0),
#line 87
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 86
            .lvl = 42,
#line 85
            .nature = NATURE_BRAVE,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 89
                MOVE_LIGHT_SCREEN,
                MOVE_PSYCHIC,
                MOVE_REFLECT,
                MOVE_METAL_CLAW,
            },
            },
            {
#line 94
            .species = SPECIES_SKARMORY,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 98
            .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 6, 252),
#line 97
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 96
            .lvl = 43,
#line 95
            .nature = NATURE_IMPISH,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 99
                MOVE_TOXIC,
                MOVE_AERIAL_ACE,
                MOVE_PROTECT,
                MOVE_STEEL_WING,
            },
            },
            {
#line 104
            .species = SPECIES_AGGRON,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 108
            .ev = TRAINER_PARTY_EVS(0, 252, 0, 0, 252, 6),
#line 107
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 106
            .lvl = 44,
#line 105
            .nature = NATURE_ADAMANT,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 109
                MOVE_THUNDER,
                MOVE_PROTECT,
                MOVE_SOLAR_BEAM,
                MOVE_DRAGON_CLAW,
            },
            },
        },
    },
