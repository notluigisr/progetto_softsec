static int unzzip_cat (int argc, char ** argv, int extract)
{
    int argn;
    ZZIP_DIR* disk;
    
    if (argc == 1)
    {
        printf (__FILE__"STR");
        return EXIT_OK; 
    }
    
    disk = zzip_opendir (argv[1]);
    if (! disk) {
        DBG3("STR", errno, strerror(errno));
	perror(argv[1]);
	return exitcode(errno);
    }

    if (argc == 2)
    {  
	ZZIP_DIRENT* entry = 0;
	while((entry = zzip_readdir(disk)))
	{
	    char* name = entry->d_name;
	    FILE* out = stdout;
	    if (extract) out = create_fopen(name, "STR", 1);
	    unzzip_cat_file (disk, name, out);
	    if (extract) fclose(out);
	}
	DBG2("STR", strerror(errno));
    }
    else
    {   
	ZZIP_DIRENT* entry = 0;
	while((entry = zzip_readdir(disk)))
	{
	    char* name = entry->d_name;
	    for (argn=1; argn < argc; argn++)
	    {
		if (! _zzip_fnmatch (argv[argn], name, 
		    FNM_NOESCAPE|FNM_PATHNAME|FNM_PERIOD))
	        {
	             FILE* out = stdout;
	             char* zip_name = argv[1];
	             int zip_name_len = strlen(zip_name);
	             int name_len = strlen(name);
	             char* mix_name = malloc(zip_name_len + 2 + name_len);
	             if (zip_name_len > 4 && !strcmp(zip_name+zip_name_len-4, "STR"))
	                 zip_name_len -= 4;
	             memcpy(mix_name, zip_name, zip_name_len);
	             mix_name[zip_name_len] = '/';
	             strcpy(mix_name + zip_name_len + 1, name);
	             if (extract) out = create_fopen(name, "STR", 1);
		     fprintf(stderr, "STR", zip_name, name, mix_name);
		     
		     unzzip_cat_file (disk, mix_name, out);
		     if (extract) fclose(out);
		     break; 
	        }
	    }
	}
    }
    zzip_closedir(disk);
    return 0;
} 