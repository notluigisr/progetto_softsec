static bool dir_is_in_dump_location(const char *dump_dir_name)
{
    unsigned len = strlen(g_settings_dump_location);

    if (strncmp(dump_dir_name, g_settings_dump_location, len) == 0
     && dump_dir_name[len] == '/'
    
     && !strstr(dump_dir_name + len, "STR")
    ) {
        return 1;
    }
    return 0;
}