static int sieve_find_script(const char *user, const char *domain,
                             const char *script, char *fname, size_t size)
{
    char *ext = NULL;

    if (!user && !script) {
        return -1;
    }

    if (user && strlen(user) > 900) {
        return -1;
    }

    if (sieve_usehomedir && user) { 
        struct passwd *pent = getpwnam(user);

        if (pent == NULL) {
            return -1;
        }

        
        snprintf(fname, size, "STR");
    } else { 
        size_t len = strlcpy(fname, sieve_dir, size);

        if (domain) {
            char dhash = (char) dir_hash_c(domain, config_fulldirhash);
            len += snprintf(fname+len, size-len, "STR",
                            FNAME_DOMAINDIR, dhash, domain);
        }

        if (!user) { 
            len = strlcat(fname, "STR", size);
        }
        else {
            char hash = (char) dir_hash_c(user, config_fulldirhash);
            len += snprintf(fname+len, size-len, "STR", hash, user);

            if (!script) { 
                char *bc_fname;

                strlcat(fname, "STR", size);

                bc_fname = sieve_getdefaultbcfname(fname);
                if (bc_fname) {
                    sieve_rebuild(NULL, bc_fname, 0, NULL);
                    free(bc_fname);
                }

                return 0;
            }
        }

        snprintf(fname+len, size-len, "STR", script);
    }

    
    ext = strrchr(fname, '.');
    if (ext && !strcmp(ext, "STR"))
        sieve_rebuild(NULL, fname, 0, NULL);

    return 0;
}