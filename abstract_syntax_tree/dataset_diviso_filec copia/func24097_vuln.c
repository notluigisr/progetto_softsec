static int unzzip_cat (int argc, char ** argv, int extract)
{
    int argn;
    ZZIP_DIR* disk;
    zzip_error_t error;
    
    if (argc == 1)
    {
        printf (__FILE__"STR");
        return EXIT_OK; 
    }
    
    disk = zzip_dir_open (argv[1], &error);
    if (! disk) {
	fprintf(stderr, "STR", argv[1], zzip_strerror(error));
	return exitcode(error);
    }

    if (argc == 2)
    {  
	ZZIP_DIRENT entry;
	while(zzip_dir_read(disk, &entry))
	{
	    char* name = entry.d_name;
	    FILE* out = stdout;
	    if (extract) out = create_fopen(name, "STR", 1);
	    if (out) {
	        unzzip_cat_file (disk, name, out);
	        if (extract) fclose(out);
	    }
	}
    }
    else
    {   
	ZZIP_DIRENT entry;
	while(zzip_dir_read(disk, &entry))
	{
	    char* name = entry.d_name;
	    for (argn=1; argn < argc; argn++)
	    {
		if (! _zzip_fnmatch (argv[argn], name, 
		    FNM_NOESCAPE|FNM_PATHNAME|FNM_PERIOD))
	        {
	            FILE* out = stdout;
	            if (extract) out = create_fopen(name, "STR", 1);
	            if (out) {
		        unzzip_cat_file (disk, name, out);
		        if (extract) fclose(out);
		    }
		    break; 
	        }
	    }
	}
    }
    zzip_dir_close(disk);
    return 0;
} 