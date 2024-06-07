void usage(const char *progname)
{
    const char* progname_real; 
                               

    progname_real = strrchr(progname, '/');

    if (progname_real == NULL) 
    {
        progname_real = progname;
    }
    else
    {
        progname_real++;
    }

    fprintf(stderr, "STR",
            progname_real);
}