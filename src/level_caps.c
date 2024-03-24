#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "level_caps.h"
#include "pokemon.h"
#include "constants/vars.h"

u32 GetCurrentLevelCap(void)
{
    static const u32 sLevelCapFlagMap[][2] =
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

    u32 i;
    if (VarGet(VAR_LEVEL_CAP_TYPE) == 1)
    {
        for (i = 0; i < ARRAY_COUNT(sLevelCapFlagMap); i++)
        {
            if (!FlagGet(sLevelCapFlagMap[i][0]))
                return sLevelCapFlagMap[i][1];
        }
    }

    return MAX_LEVEL;
}

u32 GetSoftLevelCapExpValue(u32 level, u32 expValue)
{
    static const u32 sExpScalingDown[5] = { 4, 8, 16, 32, 64 };

    u32 levelDifference;
    u32 levelCap = GetCurrentLevelCap();

    if (VarGet(VAR_LEVEL_CAP_TYPE) == 0 )
    {
        return expValue;
    }
    else if(VarGet(VAR_LEVEL_CAP_TYPE) == 1)
    {
        if(level < levelCap)
        {
            return expValue;
        }
            
        else if(level >= levelCap)
        {
            levelDifference = level - levelCap;

            if (levelDifference > ARRAY_COUNT(sExpScalingDown))
                {
                    return expValue / sExpScalingDown[ARRAY_COUNT(sExpScalingDown) - 1];
                }
            else
                {
                    return expValue / sExpScalingDown[levelDifference];
                }
        }
        else
            {
                return 0;
            }
    }
    else
    {
        return 0;
    }
}
