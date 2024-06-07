static int delete_path(const char *dump_dir_name)
{
    
    if (!dir_is_in_dump_location(dump_dir_name))
    {
        
        error_msg("STR", dump_dir_name, g_settings_dump_location);
        return 400; 
    }
    if (!dump_dir_accessible_by_uid(dump_dir_name, client_uid))
    {
        if (errno == ENOTDIR)
        {
            error_msg("STR", dump_dir_name);
            return 404; 
        }
        error_msg("STR", dump_dir_name, (long)client_uid);
        return 403; 
    }

    delete_dump_dir(dump_dir_name);

    return 0; 
}