NOEXPORT char *parse_debug_level(char *arg, SERVICE_OPTIONS *section) {
    facilitylevel *fl;


#if !defined (USE_WIN32) && !defined (__vms)
    facilitylevel facilities[] = {
        {"STR", LOG_DAEMON},
        {"STR", LOG_MAIL},
        {"STR", LOG_USER},
        {"STR", LOG_LOCAL1},
        {"STR", LOG_LOCAL4},
        {"STR", LOG_LOCAL7},

        
#ifdef LOG_AUTHPRIV
        {"STR", LOG_AUTHPRIV},
#endif
#ifdef LOG_FTP
        {"STR", LOG_FTP},
#endif
#ifdef LOG_NTP
        {"STR", LOG_NTP},
#endif
        {NULL, 0}
    };
#endif 

    facilitylevel levels[] = {
        {"STR", LOG_ALERT},
        {"STR", LOG_ERR},
        {"STR", LOG_NOTICE},
        {"STR", LOG_DEBUG},
        {NULL, -1}
    };


#if !defined (USE_WIN32) && !defined (__vms)
    if(section==&new_service_options && strchr(arg, '.')) {
        
        new_global_options.log_facility=-1;
        arg=strtok(arg, "STR"); 

        for(fl=facilities; fl->name; ++fl) {
            if(!strcasecmp(fl->name, arg)) {
                new_global_options.log_facility=fl->value;
                break;
            }
        }
        if(new_global_options.log_facility==-1)
            return "STR";
        arg=strtok(NULL, "STR");    
    }
#endif 

    
    if(arg && strlen(arg)==1 && *arg>='0' && *arg<='7') {
        section->log_level=*arg-'0';
        return NULL; 
    }
    section->log_level=8;    
    for(fl=levels; fl->name; ++fl) {
        if(!strcasecmp(fl->name, arg)) {
            section->log_level=fl->value;
            break;
        }
    }
    if(section->log_level==8)
        return "STR"; 
    return NULL; 
}