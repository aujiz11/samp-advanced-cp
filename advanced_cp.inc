// created by Ausil (#aujiz)

#if defined _include_advanced_cp_inc
    #endinput
#endif

#define _include_advanced_cp_inc

#include <streamer>
#include <PawnPlus>

#if !defined _INC_SSCANF
    #error sscanf2.inc not found
#endif

#define ADVANCEDCP_UKNOWN -1

#if !defined ADVANCEDCP_SIZE_LIMIT
    #define ADVANCEDCP_SIZE_LIMIT 7.0
#endif


static 
    enum _:E_ADVANCED_CP
    {
        cp_MapIcon,
        cp_Area
    };

static Map:map_advancedCP;

// Called when the player enters the advanced checkpoint
forward OnPlayerEnterAdvancedCP(playerid, checkpointid);

stock CreateAdvancedCP(playerid, Float:centreX, Float:centreY, Float:centreZ, Float:size)
{
    if (!map_has_key(map_advancedCP, playerid)) {
        printf("[Error] Function 'CreateAdvancedCP(%d, ...)' key does not exist.", playerid);
        return ADVANCEDCP_UKNOWN;
    }

    if (size > ADVANCEDCP_SIZE_LIMIT) {
        printf("[Error] Function 'CreateAdvancedCP(%d, %f, %f, %f, %f)' exceeds the size limit.", playerid, centreX, centreY, centreZ, size);
        return ADVANCEDCP_UKNOWN;
    }

    new Pool:pool_advancedCP = pool_new(_, true),
        index, checkpointData[E_ADVANCED_CP];

    if (map_get_safe(map_advancedCP, playerid, pool_advancedCP))
    {
        checkpointData[cp_MapIcon] = CreateDynamicMapIcon(centreX, centreY, centreZ, 0, 0xD10000FF, -1, -1, playerid, -1.0, MAPICON_GLOBAL_CHECKPOINT);
        checkpointData[cp_Area] = CreateDynamicSphere(centreX, centreY, centreZ, size, -1, -1, playerid);

        index = pool_add_arr(pool_advancedCP, checkpointData);

        map_set(map_advancedCP, playerid, pool_advancedCP);

        return index;
    }

    return ADVANCEDCP_UKNOWN;
}

stock bool:DestroyAdvancedCP(playerid, checkpointid = ADVANCEDCP_UKNOWN)
{
    if (!map_has_key(map_advancedCP, playerid)) {
        printf("[Error] Function 'DestroyAdvancedCP(%d, %d)' key does not exist.", playerid, checkpointid);
        return false;
    }

    new Pool:pool_advancedCP = pool_new(_, true),
        checkpointData[E_ADVANCED_CP];

    if (checkpointid == ADVANCEDCP_UKNOWN)
    {
        if (map_get_safe(map_advancedCP, playerid, pool_advancedCP))
        {
            for(new Iter:i=pool_iter(pool_advancedCP);iter_inside(i);iter_move_next(i))
            {
                if (iter_get_arr_safe(i, checkpointData))
                {
                    DestroyDynamicMapIcon(checkpointData[cp_MapIcon]);
                    DestroyDynamicArea(checkpointData[cp_Area]);

                    iter_erase_deep(i);
                }
            }

            map_set(map_advancedCP, playerid, pool_advancedCP);
            return true;
        }

        return false;
    }

    if (map_get_safe(map_advancedCP, playerid, pool_advancedCP))
    {
        if (checkpointid < 0 || !pool_has(pool_advancedCP, checkpointid)) {
            printf("[Error] Function 'DestroyAdvancedCP(%d, %d)' checkpointid does not exist.", playerid, checkpointid);
            return false;
        }

        if (pool_get_arr_safe(pool_advancedCP, checkpointid, checkpointData))
        {
            DestroyDynamicMapIcon(checkpointData[cp_MapIcon]);
            DestroyDynamicArea(checkpointData[cp_Area]);

            pool_remove_deep(pool_advancedCP, checkpointid);

            map_set(map_advancedCP, playerid, pool_advancedCP);
        }
        return true;
    }
    return false;
}

stock bool:IsPlayerInAdvancedCP(playerid, checkpointid)
{
    if (!map_has_key(map_advancedCP, playerid)) {
        printf("[Error] Function 'IsPlayerInAdvancedCP(%d, %d)' key does not exist.", playerid, checkpointid);
        return false;
    }

    new Pool:pool_advancedCP = pool_new(_, true),
        checkpointData[E_ADVANCED_CP];

    if (map_get_safe(map_advancedCP, playerid, pool_advancedCP))
    {
        if (checkpointid < 0 || !pool_has(pool_advancedCP, checkpointid)) {
            printf("[Error] Function 'IsPlayerInAdvancedCP(%d, %d)' checkpointid does not exist.", playerid, checkpointid);
            return false;
        }

        if (pool_get_arr_safe(pool_advancedCP, checkpointid, checkpointData))
        {
            if (IsPlayerInDynamicArea(playerid, checkpointData[cp_Area]))
                return true;
        }
    }
    return false;
}

stock bool:GetPlayerAdvancedCP(playerid, checkpointid, &Float:centreX, &Float:centreY, &Float:centreZ)
{
    if (!map_has_key(map_advancedCP, playerid)) {
        printf("[Error] Function 'GetPlayerAdvancedCP(%d, %d, ...)' key does not exist.", playerid, checkpointid);
        return false;
    }

    new Pool:pool_advancedCP = pool_new(_, true),
        checkpointData[E_ADVANCED_CP];

    if (map_get_safe(map_advancedCP, playerid, pool_advancedCP))
    {
        if (checkpointid < 0 || !pool_has(pool_advancedCP, checkpointid)) {
            printf("[Error] Function 'GetPlayerAdvancedCP(%d, %d, ...)' checkpointid does not exist.", playerid, checkpointid);
            return false;
        }

        if (pool_get_arr_safe(pool_advancedCP, checkpointid, checkpointData))
        {
            Streamer_GetItemPos(STREAMER_TYPE_AREA, checkpointData[cp_Area], centreX, centreY, centreZ);
        }
    }

    return false;
}

stock bool:IsPlayerInRangeACP(playerid, checkpointid, Float:range)
{
    if (!map_has_key(map_advancedCP, playerid)) {
        printf("[Error] Function 'IsPlayerInRangeACP(%d, %d)' key does not exist.", playerid, checkpointid);
        return false;
    }

    new Pool:pool_advancedCP = pool_new(_, true),
        checkpointData[E_ADVANCED_CP];

    if (map_get_safe(map_advancedCP, playerid, pool_advancedCP))
    {
        if (checkpointid < 0 || !pool_has(pool_advancedCP, checkpointid)) {
            printf("[Error] Function 'IsPlayerInRangeACP(%d, %d)' checkpointid does not exist.", playerid, checkpointid);
            return false;
        }
            
        if (pool_get_arr_safe(pool_advancedCP, checkpointid, checkpointData))
        {
            new Float:centreX, Float:centreY, Float:centreZ;
            Streamer_GetItemPos(STREAMER_TYPE_AREA, checkpointData[cp_Area], centreX, centreY, centreZ);

            if (IsPlayerInRangeOfPoint(playerid, range, centreX, centreY, centreZ))
                return true;
        }
    }

    return false;
}

public OnGameModeInit()
{
    map_advancedCP = map_new();
    return ACP_OnGameModeInit();
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif

#define OnGameModeInit(%0) CHAIN_PUBLIC:ACP_OnGameModeInit(%0)
CHAIN_FORWARD:ACP_OnGameModeInit() = 1;

public OnPlayerConnect(playerid)
{
    new Pool:pool_advancedCP = pool_new(_, true);

    map_add(map_advancedCP, playerid, pool_advancedCP);
    return ACP_OnPlayerConnect(playerid);
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect(%0) CHAIN_PUBLIC:ACP_OnPlayerConnect(%0)
CHAIN_FORWARD:ACP_OnPlayerConnect(playerid) = 1;

public OnPlayerDisconnect(playerid, reason)
{
    new Pool:pool_advancedCP = pool_new(_, true),
        checkpointData[E_ADVANCED_CP];
        
    if (map_get_safe(map_advancedCP, playerid, pool_advancedCP))
    {
        for(new Iter:i=pool_iter(pool_advancedCP);iter_inside(i);iter_move_next(i))
        {
            if (iter_get_arr_safe(i, checkpointData))
            {
                DestroyDynamicMapIcon(checkpointData[cp_MapIcon]);
                DestroyDynamicArea(checkpointData[cp_Area]);
            }
        }
    }

    map_remove_deep(map_advancedCP, playerid);
    return ACP_OnPlayerDisconnect(playerid, reason);
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect(%0) CHAIN_PUBLIC:ACP_OnPlayerDisconnect(%0)
CHAIN_FORWARD:ACP_OnPlayerDisconnect(playerid, reason) = 1;

public OnPlayerEnterDynamicArea(playerid, areaid)
{
    if (map_has_key(map_advancedCP, playerid))
    {
        new Pool:pool_advancedCP = pool_new(_, true),
            checkpointData[E_ADVANCED_CP];

        if (map_get_safe(map_advancedCP, playerid, pool_advancedCP))
        {
            for(new Iter:i=pool_iter(pool_advancedCP);iter_inside(i);iter_move_next(i))
            {
                if (iter_get_arr_safe(i, checkpointData))
                {
                    if (checkpointData[cp_Area] == areaid)
                    {
                        CallLocalFunction("OnPlayerEnterAdvancedCP", "dd", playerid, iter_get_key(i));
                    }
                }
            }
        }
    }
    return 1;
}