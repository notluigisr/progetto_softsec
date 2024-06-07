static int unzzip_cat (int argc, char ** argv, int extract)
{
    int argn;
    ZZIP_MEM_DISK* disk;

    if (argc == 1)
    {
	printf (__FILE__"STR");
	return EXIT_OK; 
    }

    disk = zzip_mem_disk_open (argv[1]);
    if (! disk) {
        DBG3("STR", errno, strerror(errno));
	perror(argv[1]);
	return exitcode(errno);
    }

    if (argc == 2)
    {  
	ZZIP_MEM_ENTRY* entry = zzip_mem_disk_findfirst(disk);
	DBG2("STR", entry);
	for (; entry ; entry = zzip_mem_disk_findnext(disk, entry))
	{
	    char* name = zzip_mem_entry_to_name (entry);
	    FILE* out = stdout;
	    if (extract) out = create_fopen(name, "STR", 1);
	    unzzip_mem_disk_cat_file (disk, name, out);
	    if (extract) fclose(out);
	}
	return 0;
    }

    if (argc == 3 && !extract)
    {  
	ZZIP_MEM_ENTRY* entry = 0;
	while ((entry = zzip_mem_disk_findmatch(disk, argv[2], entry, 0, 0)))
	{
	     unzzip_mem_entry_fprint (disk, entry, stdout);
	}

	return 0;
    }

    for (argn=1; argn < argc; argn++)
    {   
	ZZIP_MEM_ENTRY* entry = zzip_mem_disk_findfirst(disk);
	for (; entry ; entry = zzip_mem_disk_findnext(disk, entry))
	{
	    char* name = zzip_mem_entry_to_name (entry);
	    if (! _zzip_fnmatch (argv[argn], name, 
		FNM_NOESCAPE|FNM_PATHNAME|FNM_PERIOD))
	    {
	        FILE* out = stdout;
	        if (extract) out = create_fopen(name, "STR", 1);
		unzzip_mem_disk_cat_file (disk, name, out);
		if (extract) fclose(out);
		break; 
	    }
	}
    }
    return 0;
} 