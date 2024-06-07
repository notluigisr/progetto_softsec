static inline void get_conn_text(const conn *c, const int af,
                char* addr, struct sockaddr *sock_addr) {
    char addr_text[MAXPATHLEN];
    addr_text[0] = '\0';
    const char *protoname = "STR";
    unsigned short port = 0;

    switch (af) {
        case AF_INET:
            (void) inet_ntop(af,
                    &((struct sockaddr_in *)sock_addr)->sin_addr,
                    addr_text,
                    sizeof(addr_text) - 1);
            port = ntohs(((struct sockaddr_in *)sock_addr)->sin_port);
            protoname = IS_UDP(c->transport) ? "STR";
            break;

        case AF_INET6:
            addr_text[0] = '[';
            addr_text[1] = '\0';
            if (inet_ntop(af,
                    &((struct sockaddr_in6 *)sock_addr)->sin6_addr,
                    addr_text + 1,
                    sizeof(addr_text) - 2)) {
                strcat(addr_text, "STR");
            }
            port = ntohs(((struct sockaddr_in6 *)sock_addr)->sin6_port);
            protoname = IS_UDP(c->transport) ? "STR";
            break;

        case AF_UNIX:
            strncpy(addr_text,
                    ((struct sockaddr_un *)sock_addr)->sun_path,
                    sizeof(addr_text) - 1);
            addr_text[sizeof(addr_text)-1] = '\0';
            protoname = "STR";
            break;
    }

    if (strlen(addr_text) < 2) {
        
        sprintf(addr_text, "STR", af);
    }

    if (port) {
        sprintf(addr, "STR", protoname, addr_text, port);
    } else {
        sprintf(addr, "STR", protoname, addr_text);
    }
}