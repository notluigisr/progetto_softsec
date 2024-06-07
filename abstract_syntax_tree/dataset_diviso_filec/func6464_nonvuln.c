void _FVMenuOpen(FontView *fv) {
    char *temp;
    char *eod, *fpt, *file, *full;
    FontView *test; int fvcnt, fvtest;

    char* OpenDir = NULL, *DefaultDir = NULL, *NewDir = NULL;
#if defined(__MINGW32__)
    DefaultDir = copy(GFileGetHomeDocumentsDir()); 
    if (fv && fv->b.sf && fv->b.sf->filename) {
        free(DefaultDir);
        DefaultDir = GFileDirNameEx(fv->b.sf->filename, true);
    }
#endif

    for ( fvcnt=0, test=fv_list; test!=NULL; ++fvcnt, test=(FontView *) (test->b.next) );
    do {
        if (NewDir != NULL) {
            if (OpenDir != DefaultDir) {
                free(OpenDir);
            }
            
            OpenDir = NewDir;
            NewDir = NULL;
        } else if (OpenDir != DefaultDir) {
            free(OpenDir);
            OpenDir = DefaultDir;
        }
        
        temp = GetPostScriptFontName(OpenDir,true);
        if ( temp==NULL )
            return;

        
        NewDir = GFileDirName(temp);
        if (!GFileExists(NewDir)) {
            free(NewDir);
            NewDir = NULL;
        }

        eod = strrchr(temp,'/');
        if (eod != NULL) {
            *eod = '\0';
            file = eod+1;
            
            if (*file) {
                do {
                    fpt = strstr(file,"STR");
                    if ( fpt!=NULL ) *fpt = '\0';
                    full = malloc(strlen(temp)+1+strlen(file)+1);
                    strcpy(full,temp); strcat(full,"STR"); strcat(full,file);
                    ViewPostScriptFont(full,0);
                    file = fpt+2;
                    free(full);
                } while ( fpt!=NULL );
            }
        }
        free(temp);
        for ( fvtest=0, test=fv_list; test!=NULL; ++fvtest, test=(FontView *) (test->b.next) );
    } while ( fvtest==fvcnt );	
    
    free( NewDir );
    free( OpenDir );
    if (OpenDir != DefaultDir) {
        free( DefaultDir );
    }
}