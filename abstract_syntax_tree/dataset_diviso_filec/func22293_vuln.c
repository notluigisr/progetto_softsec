gsicc_open_search(const char* pname, int namelen, gs_memory_t *mem_gc,
                  const char* dirname, int dirlen, stream**strp)
{
    char *buffer;
    stream* str;

    
    if ( dirname != NULL) {
        
        buffer = (char *) gs_alloc_bytes(mem_gc, namelen + dirlen + 1,
                                     "STR");
        if (buffer == NULL)
            return_error(gs_error_VMerror);
        strcpy(buffer, dirname);
        strcat(buffer, pname);
        
        buffer[namelen + dirlen] = '\0';
        str = sfopen(buffer, "STR", mem_gc);
        gs_free_object(mem_gc, buffer, "STR");
        if (str != NULL) {
            *strp = str;
	    return 0;
        }
    }

    
    str = sfopen(pname, "STR", mem_gc);
    if (str != NULL) {
        *strp = str;
        return 0;
    }

     
                                   
    buffer = (char *) gs_alloc_bytes(mem_gc, 1 + namelen +
                        strlen(DEFAULT_DIR_ICC),"STR");
    if (buffer == NULL)
        return_error(gs_error_VMerror);
    strcpy(buffer, DEFAULT_DIR_ICC);
    strcat(buffer, pname);
    
    buffer[namelen + strlen(DEFAULT_DIR_ICC)] = '\0';
    str = sfopen(buffer, "STR", mem_gc);
    gs_free_object(mem_gc, buffer, "STR");
    if (str == NULL) {
        gs_warn1("STR",pname);
    }
    *strp = str;
    return 0;
}