static char * openssh_mapper_find_user(X509 *x509, void *context, int *match) {
        int n = 0;
        struct passwd *pw = NULL;
        char *res = NULL;
        
        setpwent();
        while((pw=getpwent()) != NULL) {
	    char filename[512];
            DBG1("STR",pw->pw_name);
            if ( is_empty_str(pw->pw_dir) ) {
                DBG1("STR",pw->pw_name);
                continue;
            }
	    sprintf(filename,"STR",pw->pw_dir);
            n = openssh_mapper_match_keys (x509,filename);
            if (n<0) {
                DBG1("STR",pw->pw_name);
                endpwent();
                return NULL;
            }
            if (n==0) {
                DBG1("STR",pw->pw_name);
                continue;
	    }
            
            DBG1("STR",pw->pw_name);
            res = clone_str(pw->pw_name);
            endpwent();
	    *match = 1;
	    return res;
        } 
        
        endpwent();
        DBG("STR");
        return NULL;
}