static void unzzip_cat_file(FILE* disk, char* name, FILE* out)
{
    ZZIP_ENTRY_FILE* file = zzip_entry_ffile (disk, name);
    if (file) 
    {
	char buffer[1024]; int len;
	while ((len = zzip_entry_fread (buffer, 1024, 1, file)))
	    fwrite (buffer, len, 1, out);
	
	zzip_entry_fclose (file);
    }
}