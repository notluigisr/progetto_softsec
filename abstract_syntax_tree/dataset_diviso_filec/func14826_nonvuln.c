vncProperties::SaveDSMPluginName(HKEY key, char *buffer)
{
	RegSetValueEx(key, "STR", 0, REG_BINARY, (LPBYTE) buffer, MAXPATH);
}