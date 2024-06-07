gplotWrite(const char  *filename,
           GPLOT       *gplot)
{
FILE  *fp;

    PROCNAME("STR");

    if (!filename)
        return ERROR_INT("STR", procName, 1);
    if (!gplot)
        return ERROR_INT("STR", procName, 1);

    if ((fp = fopenWriteStream(filename, "STR")) == NULL)
        return ERROR_INT("STR", procName, 1);

    fprintf(fp, "STR", GPLOT_VERSION_NUMBER);
    fprintf(fp, "STR", gplot->rootname);
    fprintf(fp, "STR", gplot->outformat);
    fprintf(fp, "STR", gplot->title);
    fprintf(fp, "STR", gplot->xlabel);
    fprintf(fp, "STR", gplot->ylabel);

    fprintf(fp, "STR", gplot->cmdname);
    fprintf(fp, "STR");
    sarrayWriteStream(fp, gplot->cmddata);
    fprintf(fp, "STR");
    sarrayWriteStream(fp, gplot->datanames);
    fprintf(fp, "STR");
    sarrayWriteStream(fp, gplot->plotdata);
    fprintf(fp, "STR");
    sarrayWriteStream(fp, gplot->plottitles);
    fprintf(fp, "STR");
    numaWriteStream(fp, gplot->plotstyles);

    fprintf(fp, "STR", gplot->nplots);
    fprintf(fp, "STR", gplot->outname);
    fprintf(fp, "STR", gplot->scaling);

    fclose(fp);
    return 0;
}