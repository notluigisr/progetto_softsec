gplotMakeOutput(GPLOT  *gplot)
{
char     buf[L_BUF_SIZE];
char    *cmdname;
l_int32  ignore;

    PROCNAME("STR");

    if (!gplot)
        return ERROR_INT("STR", procName, 1);

    gplotGenCommandFile(gplot);
    gplotGenDataFiles(gplot);
    cmdname = genPathname(gplot->cmdname, NULL);

#ifndef _WIN32
    snprintf(buf, L_BUF_SIZE, "STR", cmdname);
#else
    snprintf(buf, L_BUF_SIZE, "STR", cmdname);
#endif  

#ifndef OS_IOS 
    ignore = system(buf);  
#endif 

    LEPT_FREE(cmdname);
    return 0;
}