#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "level_caps.h"
#include "pokemon.h"
#include "../include/constants/vars.h"

static EWRAM_DATA u8 B_EXP_CAP_TYPE = EXP_CAP_NONE;              // [EXP_CAP_NONE, EXP_CAP_HARD, EXP_CAP_SOFT] choose the type of level cap to apply
static EWRAM_DATA u8 B_LEVEL_CAP_TYPE = LEVEL_CAP_NONE;          // [LEVEL_CAP_NONE, LEVEL_CAP_FLAG_LIST, LEVEL_CAP_VARIABLE] choose the method to derive the level cap
u32 GetCurrentLevelCap(void)
{
    // Da aggiustare i livelli in base al gioco
    static const u32 sLevelCapFlagMap_Nuzlocke[][2] =
    {
        {FLAG_BADGE01_GET, 15},
        {FLAG_BADGE02_GET, 19},
        {FLAG_BADGE03_GET, 24},
        {FLAG_BADGE04_GET, 29},
        {FLAG_BADGE05_GET, 31},
        {FLAG_BADGE06_GET, 33},
        {FLAG_BADGE07_GET, 42},
        {FLAG_BADGE08_GET, 46},
        {FLAG_IS_CHAMPION, 58},
    };

        static const u32 sLevelCapFlagMap_Hard[][2] =
    {
        {FLAG_BADGE01_GET, 10},
        {FLAG_BADGE02_GET, 19},
        {FLAG_BADGE03_GET, 24},
        {FLAG_BADGE04_GET, 29},
        {FLAG_BADGE05_GET, 31},
        {FLAG_BADGE06_GET, 33},
        {FLAG_BADGE07_GET, 42},
        {FLAG_BADGE08_GET, 46},
        {FLAG_IS_CHAMPION, 58},
    };

    u32 i;

        //Check the var for the game mode selection
    if (VAR_GAME_MODE == 1) {
        B_EXP_CAP_TYPE = EXP_CAP_HARD;
        B_LEVEL_CAP_TYPE = LEVEL_CAP_FLAG_LIST;
    } else if (VAR_GAME_MODE == 2){
        B_EXP_CAP_TYPE = EXP_CAP_SOFT;
        B_LEVEL_CAP_TYPE = LEVEL_CAP_FLAG_LIST;
    }

    if (B_LEVEL_CAP_TYPE == LEVEL_CAP_FLAG_LIST)
    {
        if (B_EXP_CAP_TYPE == EXP_CAP_SOFT) {
            for (i = 0; i < ARRAY_COUNT(sLevelCapFlagMap_Nuzlocke); i++)
            {
                if (!FlagGet(sLevelCapFlagMap_Nuzlocke[i][0]))
                    return sLevelCapFlagMap_Nuzlocke[i][1];
            }
        } else if (B_EXP_CAP_TYPE == EXP_CAP_HARD) {
            for (i = 0; i < ARRAY_COUNT(sLevelCapFlagMap_Hard); i++)
            {
                if (!FlagGet(sLevelCapFlagMap_Hard[i][0]))
                    return sLevelCapFlagMap_Hard[i][1];
            }
        }
    }
    else if (B_LEVEL_CAP_TYPE == LEVEL_CAP_VARIABLE)
    {
        return VarGet(B_LEVEL_CAP_VARIABLE);
    }

    return MAX_LEVEL;
}

u32 GetSoftLevelCapExpValue(u32 level, u32 expValue)
{
    static const u32 sExpScalingDown[5] = { 4, 8, 16, 32, 64 };
    static const u32 sExpScalingUp[5]   = { 16, 8, 4, 2, 1 };

    u32 levelDifference;
    u32 currentLevelCap = GetCurrentLevelCap();

    if (B_EXP_CAP_TYPE == EXP_CAP_NONE)
        return expValue;

    if (B_LEVEL_CAP_EXP_UP && level < currentLevelCap)
    {
        levelDifference = currentLevelCap - level;
        if (levelDifference > ARRAY_COUNT(sExpScalingDown))
            return expValue + (expValue / sExpScalingUp[ARRAY_COUNT(sExpScalingDown) - 1]);
        else
            return expValue + (expValue / sExpScalingUp[levelDifference]);
    }
    else if (level < currentLevelCap)
    {
       return expValue;
    }
    return 0;
}
