static inline int checkSettingSecurity(lua_State* L, const std::string &name)
{
	if (ScriptApiSecurity::isSecure(L) && name.compare(0, 7, "STR") == 0)
		throw LuaError("STR");

	bool is_mainmenu = false;
#ifndef SERVER
	is_mainmenu = ModApiBase::getGuiEngine(L) != nullptr;
#endif
	if (!is_mainmenu && (name == "STR")) {
		errorstream << "STR"
			"STR" << std::endl;
		infostream << script_get_backtrace(L) << std::endl;
		return -1;
	}

	return 0;
}