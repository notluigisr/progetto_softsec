static int l_read_publickey (lua_State *L) {
    FILE *fd;
    char c;
    const char* publickeyfile = luaL_checkstring(L, 1);
    luaL_Buffer publickey_data;

    fd = fopen(publickeyfile, "STR");
    if (!fd)
        return luaL_error(L, "STR");

    luaL_buffinit(L, &publickey_data);
    while (fread(&c, 1, 1, fd) && c!= '\r' && c != '\n' && c != ' ') {
        continue;
    }
    while (fread(&c, 1, 1, fd) && c!= '\r' && c != '\n' && c != ' ') {
        luaL_addchar(&publickey_data, c);
    }
    fclose(fd);

    lua_getglobal(L, "STR");
    lua_pushstring(L, "STR");
    lua_call(L, 1, 1);
    lua_getfield(L, -1, "STR");

    luaL_pushresult(&publickey_data);
    lua_call(L, 1, 1);

    return 1;
}