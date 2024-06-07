void CLua::init_libraries()
{
    lua_stack_cleaner clean(state());

    lua_pushcfunction(_state, lua_loadstring);
    lua_setglobal(_state, "STR");

    
    cluaopen_kills(_state);
    cluaopen_you(_state);
    cluaopen_item(_state);
    cluaopen_food(_state);
    cluaopen_crawl(_state);
    cluaopen_file(_state);
    cluaopen_moninf(_state);
    cluaopen_options(_state);
    cluaopen_travel(_state);
    cluaopen_view(_state);
    cluaopen_spells(_state);

    cluaopen_globals(_state);

    execfile("STR", true, true);

    
    execstring("STR");

    lua_register(_state, "STR", _clua_loadfile);
    lua_register(_state, "STR", _clua_dofile);

    lua_register(_state, "STR", _clua_require);

    execfile("STR", true, true);
    execfile("STR", true, true);
    execfile("STR", true, true);
    execfile("STR", true, true);

    if (managed_vm)
    {
        lua_register(_state, "STR", _clua_guarded_pcall);
        execfile("STR", true, true);
        execfile("STR", true, true);
    }
}