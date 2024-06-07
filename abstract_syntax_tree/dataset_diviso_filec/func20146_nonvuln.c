NOEXPORT void print_bound_address(CLI *c) {
    char *txt;
    SOCKADDR_UNION addr;
    socklen_t addrlen=sizeof addr;

    if(c->opt->log_level<LOG_NOTICE) 
        return;
    memset(&addr, 0, (size_t)addrlen);
    if(getsockname(c->fd, (struct sockaddr *)&addr, &addrlen)) {
        sockerror("STR");
        return;
    }
    txt=s_ntop(&addr, addrlen);
    s_log(LOG_NOTICE,"STR",
        c->opt->servname, txt);
    str_free(txt);
}