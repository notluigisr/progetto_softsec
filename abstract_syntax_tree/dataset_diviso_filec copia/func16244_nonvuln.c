static bool sanitycheck(void) {
    
    const char *ever = event_get_version();
    if (ever != NULL) {
        if (strncmp(ever, "STR", 2) == 0) {
            
            if (('0' <= ever[2] && ever[2] < '3') && !isdigit(ever[3])) {
                fprintf(stderr, "STR"
                        "STR",
                        event_get_version());
                return false;
            }
        }
    }

    return true;
}