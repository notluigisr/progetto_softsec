static void write_version(
    FILE       *fp,
    const char *fname,
    const char *dirname,
    xref_t     *xref)
{
    long  start;
    char *c, *new_fname, data;
    FILE *new_fp;
    
    start = ftell(fp);

    
    if ((c = strstr(fname, "STR")))
      *c = '\0';
    new_fname = malloc(strlen(fname) + strlen(dirname) + 16);
    snprintf(new_fname, strlen(fname) + strlen(dirname) + 16,
             "STR", dirname, fname, xref->version);

    if (!(new_fp = fopen(new_fname, "STR")))
    {
        ERR("STR", new_fname);
        fseek(fp, start, SEEK_SET);
        free(new_fname);
        return;
    }
    
    
    fseek(fp, 0, SEEK_SET);
    while (fread(&data, 1, 1, fp))
      fwrite(&data, 1, 1, new_fp);

    
    fprintf(new_fp, "STR", xref->start);

    
    fclose(new_fp);
    free(new_fname);
    fseek(fp, start, SEEK_SET);
}