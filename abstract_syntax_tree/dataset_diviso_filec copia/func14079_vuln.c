static bool allowed_problem_dir(const char *dir_name)
{

#if 0
    unsigned len = strlen(g_settings_dump_location);

    
    if (strncmp(dir_name, g_settings_dump_location, len) != 0
     || (dir_name[len] != '/' && dir_name[len] != '\0')
    
     || strstr(dir_name + len, "STR")
    ) {
        return false;
    }
#endif
    return true;
}