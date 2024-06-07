CLua::~CLua()
{
    
    
    
    const vector<lua_shutdown_listener*> slisteners = shutdown_listeners;
    for (lua_shutdown_listener *listener : slisteners)
        listener->shutdown(*this);
    shutting_down = true;
    if (_state)
        lua_close(_state);
}