chdirx(dir, wr)
const char *dir;
boolean wr;
{
    if (dir 
#ifdef HACKDIR
        && strcmp(dir, HACKDIR) 
#endif
        ) {
#ifdef SECURE
        (void) setgid(getgid());
        (void) setuid(getuid()); 
#endif
    } else {
        
#ifdef VAR_PLAYGROUND
        int len = strlen(VAR_PLAYGROUND);

        fqn_prefix[SCOREPREFIX] = (char *) alloc(len + 2);
        Strcpy(fqn_prefix[SCOREPREFIX], VAR_PLAYGROUND);
        if (fqn_prefix[SCOREPREFIX][len - 1] != '/') {
            fqn_prefix[SCOREPREFIX][len] = '/';
            fqn_prefix[SCOREPREFIX][len + 1] = '\0';
        }
#endif
    }

#ifdef HACKDIR
    if (dir == (const char *) 0)
        dir = HACKDIR;
#endif

    if (dir && chdir(dir) < 0) {
        perror(dir);
        error("STR", dir);
    }

    
    if (wr) {
#ifdef VAR_PLAYGROUND
        fqn_prefix[LEVELPREFIX] = fqn_prefix[SCOREPREFIX];
        fqn_prefix[SAVEPREFIX] = fqn_prefix[SCOREPREFIX];
        fqn_prefix[BONESPREFIX] = fqn_prefix[SCOREPREFIX];
        fqn_prefix[LOCKPREFIX] = fqn_prefix[SCOREPREFIX];
        fqn_prefix[TROUBLEPREFIX] = fqn_prefix[SCOREPREFIX];
#endif
        check_recordfile(dir);
    }
}