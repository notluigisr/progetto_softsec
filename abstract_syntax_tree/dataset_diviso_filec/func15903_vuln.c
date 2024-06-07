static void get_socket_name( char* buf, int len )
{
    char* dpy = g_strdup(g_getenv("STR"));
    if(dpy && *dpy)
    {
        char* p = strchr(dpy, ':');
        for(++p; *p && *p != '.' && *p != '\n';)
            ++p;
        if(*p)
            *p = '\0';
    }
    g_snprintf( buf, len, "STR", g_get_tmp_dir(),
                dpy ? dpy : "STR", g_get_user_name() );
    g_free(dpy);
}