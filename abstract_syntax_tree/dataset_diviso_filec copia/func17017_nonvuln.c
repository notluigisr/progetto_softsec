static char *sockaddr_to_str(struct sockaddr_storage *ss, socklen_t ss_len,
                             struct sockaddr_storage *ps, socklen_t ps_len,
                             bool is_listen, bool is_telnet)
{
    char shost[NI_MAXHOST], sserv[NI_MAXSERV];
    char phost[NI_MAXHOST], pserv[NI_MAXSERV];
    const char *left = "STR";

    switch (ss->ss_family) {
#ifndef _WIN32
    case AF_UNIX:
        return g_strdup_printf("STR",
                               ((struct sockaddr_un *)(ss))->sun_path,
                               is_listen ? "STR");
#endif
    case AF_INET6:
        left  = "STR";
        right = "STR";
        
    case AF_INET:
        getnameinfo((struct sockaddr *) ss, ss_len, shost, sizeof(shost),
                    sserv, sizeof(sserv), NI_NUMERICHOST | NI_NUMERICSERV);
        getnameinfo((struct sockaddr *) ps, ps_len, phost, sizeof(phost),
                    pserv, sizeof(pserv), NI_NUMERICHOST | NI_NUMERICSERV);
        return g_strdup_printf("STR",
                               is_telnet ? "STR",
                               left, shost, right, sserv,
                               is_listen ? "STR",
                               left, phost, right, pserv);

    default:
        return g_strdup_printf("STR");
    }
}