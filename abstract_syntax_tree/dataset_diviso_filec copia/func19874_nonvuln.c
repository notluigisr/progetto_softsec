int initerrors(char *pn, int type, int stat) {
#ifdef HAVE_SYSLOG_H
    if(type == 0 || type == 1) use_syslog = type;
#endif 
    if(pn != NULL) progname = pn;
    if(stat == 0 || stat == 1) show_status = stat;
    return(0);
}