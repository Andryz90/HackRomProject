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
#line 16
            .species = SPECIES_KIRLIA,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 16
            .heldItem = ITEM_SITRUS_BERRY,
#line 20
            .iv = TRAINER_PARTY_IVS(31, 0, 31, 31, 31, 31),
#line 17
            .ability = ABILITY_TRACE,
#line 18
            .lvl = 22,
#line 19
            .nature = NATURE_BOLD,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 21
                MOVE_PSYBEAM,
                MOVE_LIFE_DEW,
                MOVE_DRAINING_KISS,
            },
            },
            {
#line 25
            .species = SPECIES_AZUMARILL,
#line 25
            .gender = TRAINER_MON_MALE,
#line 29
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 26
            .ability = ABILITY_HUGE_POWER,
#line 27
            .lvl = 21,
#line 28
            .nature = NATURE_ADAMANT,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 29
                MOVE_HELPING_HAND,
                MOVE_AQUA_TAIL,
                MOVE_BOUNCE,
                MOVE_CHARM,
            },
            },
            {
#line 34
            .species = SPECIES_DEDENNE,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 34
            .heldItem = ITEM_ORAN_BERRY,
#line 37
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 35
            .ability = ABILITY_CHEEK_POUCH,
#line 36
            .lvl = 21,
            .nature = NATURE_HARDY,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 37
                MOVE_NUZZLE,
                MOVE_DRAINING_KISS,
                MOVE_THUNDER_SHOCK,
            },
            },
        },
    },
#line 41
    [PARTNER_STEVEN] =
    {
#line 42
        .trainerName = _("STEVEN"),
#line 43
        .trainerClass = TRAINER_CLASS_RIVAL,
#line 44
        .trainerPic = TRAINER_BACK_PIC_STEVEN,
        .encounterMusic_gender = 
#line 46
            TRAINER_ENCOUNTER_MUSIC_MALE,
        .partySize = 3,
        .party = (const struct TrainerMon[])
        {
            {
#line 48
            .species = SPECIES_METANG,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 52
            .ev = TRAINER_PARTY_EVS(0, 252, 252, 0, 6, 0),
#line 51
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 50
            .lvl = 42,
#line 49
            .nature = NATURE_BRAVE,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 53
                MOVE_LIGHT_SCREEN,
                MOVE_PSYCHIC,
                MOVE_REFLECT,
                MOVE_METAL_CLAW,
            },
            },
            {
#line 58
            .species = SPECIES_SKARMORY,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 62
            .ev = TRAINER_PARTY_EVS(252, 0, 0, 0, 6, 252),
#line 61
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 60
            .lvl = 43,
#line 59
            .nature = NATURE_IMPISH,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 63
                MOVE_TOXIC,
                MOVE_AERIAL_ACE,
                MOVE_PROTECT,
                MOVE_STEEL_WING,
            },
            },
            {
#line 68
            .species = SPECIES_AGGRON,
            .gender = TRAINER_MON_RANDOM_GENDER,
#line 72
            .ev = TRAINER_PARTY_EVS(0, 252, 0, 0, 252, 6),
#line 71
            .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31),
#line 70
            .lvl = 44,
#line 69
            .nature = NATURE_ADAMANT,
            .dynamaxLevel = MAX_DYNAMAX_LEVEL,
            .moves = {
#line 73
                MOVE_THUNDER,
                MOVE_PROTECT,
                MOVE_SOLAR_BEAM,
                MOVE_DRAGON_CLAW,
            },
            },
        },
    },
