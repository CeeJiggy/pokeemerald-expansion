#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "caps.h"
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
    static const u32 sExpScalingDown[5] = {4, 8, 16, 32, 64};

    u32 levelDifference;
    u32 levelCap = GetCurrentLevelCap();

    if (VarGet(VAR_LEVEL_CAP_TYPE) == 0)
    {
        return expValue;
    }
    else if (VarGet(VAR_LEVEL_CAP_TYPE) == 1)
    {
        if (level < levelCap)
        {
            return expValue;
        }

        else if (level >= levelCap)
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
        {
            return 0;
        }
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
