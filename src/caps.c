#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "caps.h"
#include "pokemon.h"
#include "../include/constants/vars.h"
#include "../include/event_data.h"


u32 GetCurrentLevelCap(void)
{
    // Da aggiustare i livelli in base al gioco
    static const u32 sLevelCapFlagMap_Nuzlocke[][2] =
    {
        {FLAG_PETALBURG_WOODS,  15},
        {FLAG_BADGE01_GET,      18},
        {FLAG_WALLY_RUSTURF,    22},
        {FLAG_BADGE02_GET,      25},
        {FLAG_RIVAL_110,        30},
        {FLAG_BADGE03_GET,      34},
        {FLAG_HIDE_METEOR_FALLS_TEAM_AQUA, 38}, //Non Boss Level Cap Flag
        //TODO Level 42ish for MT Chitney
        {FLAG_BADGE04_GET,      45},
        //TODO Level 50ish Desert for Regirock
        {FLAG_BADGE05_GET,      60},
        {FLAG_BADGE06_GET,      60},
        {FLAG_BADGE07_GET,      60},
        {FLAG_BADGE08_GET,      60},
        {FLAG_IS_CHAMPION,      60},
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
    u16* B_EXP_CAP_TYPE = GetVarPointer(VAR_GAME_MODE);
        //Check the var for the game mode selection
    if (B_LEVEL_CAP_TYPE == LEVEL_CAP_FLAG_LIST)
    {
        if (*B_EXP_CAP_TYPE == EXP_CAP_NUZLOCKE) {
            for (i = 0; i < ARRAY_COUNT(sLevelCapFlagMap_Nuzlocke); i++)
            {
                if (!FlagGet(sLevelCapFlagMap_Nuzlocke[i][0]))
                    return sLevelCapFlagMap_Nuzlocke[i][1];
            }
        } else if (*B_EXP_CAP_TYPE == EXP_CAP_HARD) {
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
    u16* B_EXP_CAP_TYPE = GetVarPointer(VAR_GAME_MODE);

    if (*B_EXP_CAP_TYPE == EXP_CAP_NONE)
        return expValue;

    if (level < currentLevelCap)
    {
        if (B_LEVEL_CAP_EXP_UP)
    {
        levelDifference = currentLevelCap - level;
            if (levelDifference > ARRAY_COUNT(sExpScalingUp))
                return expValue + (expValue / sExpScalingUp[ARRAY_COUNT(sExpScalingUp) - 1]);
        else
            return expValue + (expValue / sExpScalingUp[levelDifference]);
    }
        else
    {
       return expValue;
    }
    }
    else if (*B_EXP_CAP_TYPE == EXP_CAP_HARD)
    {
    return 0;
    }
    else if (*B_EXP_CAP_TYPE == EXP_CAP_NUZLOCKE)
    {
        levelDifference = level - currentLevelCap;
        if (levelDifference > ARRAY_COUNT(sExpScalingDown))
            return expValue / sExpScalingDown[ARRAY_COUNT(sExpScalingDown) - 1];
        else
            return expValue / sExpScalingDown[levelDifference];
    }
    else
    {
       return expValue;
    }
}

u32 GetCurrentEVCap(void)
{

    static const u16 sEvCapFlagMap[][2] = {
        // Define EV caps for each milestone
        {FLAG_BADGE01_GET, 30},
        {FLAG_BADGE02_GET, 90},
        {FLAG_BADGE03_GET, 150},
        {FLAG_BADGE04_GET, 210},
        {FLAG_BADGE05_GET, 270},
        {FLAG_BADGE06_GET, 330},
        {FLAG_BADGE07_GET, 390},
        {FLAG_BADGE08_GET, 450},
        {FLAG_IS_CHAMPION, MAX_TOTAL_EVS},
    };

    if (B_EV_CAP_TYPE == EV_CAP_FLAG_LIST)
    {
        for (u32 evCap = 0; evCap < ARRAY_COUNT(sEvCapFlagMap); evCap++)
        {
            if (!FlagGet(sEvCapFlagMap[evCap][0]))
                return sEvCapFlagMap[evCap][1];
        }
    }
    else if (B_EV_CAP_TYPE == EV_CAP_VARIABLE)
    {
        return VarGet(B_EV_CAP_VARIABLE);
    }
    else if (B_EV_CAP_TYPE == EV_CAP_NO_GAIN)
    {
        return 0;
    }

    return MAX_TOTAL_EVS;
}
