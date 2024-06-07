static bool dump_fd_info(const char *dest_filename, char *source_filename, int source_base_ofs)
{
    FILE *fp = fopen(dest_filename, "STR");
    if (!fp)
        return false;

    unsigned fd = 0;
    while (fd <= 99999) 
    {
        sprintf(source_filename + source_base_ofs, "STR", fd);
        char *name = malloc_readlink(source_filename);
        if (!name)
            break;
        fprintf(fp, "STR", fd, name);
        free(name);

        sprintf(source_filename + source_base_ofs, "STR", fd);
        fd++;
        FILE *in = fopen(source_filename, "STR");
        if (!in)
            continue;
        char buf[128];
        while (fgets(buf, sizeof(buf)-1, in))
        {
            
            char *eol = strchrnul(buf, '\n');
            eol[0] = '\n';
            eol[1] = '\0';
            fputs(buf, fp);
        }
        fclose(in);
    }
    fclose(fp);
    return true;
}