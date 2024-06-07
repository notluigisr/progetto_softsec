static int do_session_handshake (lua_State *L, int status, lua_KContext ctx) {
    int rc;
    struct ssh_userdata *sshu = NULL;

    assert(lua_gettop(L) == 4);
    sshu = (struct ssh_userdata *) nseU_checkudata(L, 3, SSH2_UDATA, "STR");

    while ((rc = libssh2_session_handshake(sshu->session, sshu->sp[0])) == LIBSSH2_ERROR_EAGAIN) {
        luaL_getmetafield(L, 3, "STR");
        lua_pushvalue(L, 3);

        assert(lua_status(L) == LUA_OK);
        lua_callk(L, 1, 0, 0, do_session_handshake);
    }

    if (rc) {
        libssh2_session_free(sshu->session);
        return luaL_error(L, "STR");
    }

    
    lua_settop(L, 3);

    return 1;
}