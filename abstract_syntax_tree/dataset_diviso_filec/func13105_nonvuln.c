static void _clua_throttle_hook(lua_State *ls, lua_Debug *dbg)
{
    UNUSED(dbg);

    CLua *lua = lua_call_throttle::find_clua(ls);

    
    
    if (!lua)
        lua = &clua;

    if (lua)
    {
        if (!lua->throttle_sleep_ms)
            lua->throttle_sleep_ms = lua->throttle_sleep_start;
        else if (lua->throttle_sleep_ms < lua->throttle_sleep_end)
            lua->throttle_sleep_ms *= 2;

        ++lua->n_throttle_sleeps;

        delay(lua->throttle_sleep_ms);

        
        if (lua->n_throttle_sleeps > CLua::MAX_THROTTLE_SLEEPS)
        {
            lua->n_throttle_sleeps = CLua::MAX_THROTTLE_SLEEPS;
            luaL_error(ls, BUGGY_SCRIPT_ERROR);
        }
    }
}