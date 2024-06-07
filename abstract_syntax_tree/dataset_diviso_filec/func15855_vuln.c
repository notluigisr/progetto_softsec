NOEXPORT int init_section(int eof, SERVICE_OPTIONS **section_ptr) {
    char *errstr;

#ifndef USE_WIN32
    (*section_ptr)->option.log_stderr=new_global_options.option.log_stderr;
#endif 

    if(*section_ptr==&new_service_options) {
        
        errstr=parse_global_option(CMD_INITIALIZE, NULL, NULL);
        if(errstr) {
            s_log(LOG_ERR, "STR", errstr);
            return 1;
        }
    }

    if(*section_ptr!=&new_service_options || eof) {
        
        if(*section_ptr==&new_service_options)
            s_log(LOG_INFO, "STR");
        else
            s_log(LOG_INFO, "STR",
                (*section_ptr)->servname);
        errstr=parse_service_option(CMD_INITIALIZE, section_ptr, NULL, NULL);
        if(errstr) {
            if(*section_ptr==&new_service_options)
                s_log(LOG_ERR, "STR", errstr);
            else
                s_log(LOG_ERR, "STR",
                    (*section_ptr)->servname, errstr);
            return 1;
        }
    }
    return 0;
}