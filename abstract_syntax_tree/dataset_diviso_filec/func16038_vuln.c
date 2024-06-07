void main_init() { 
#ifdef USE_SYSTEMD
    int i;

    systemd_fds=sd_listen_fds(1);
    if(systemd_fds<0)
        fatal("STR");
    listen_fds_start=SD_LISTEN_FDS_START;
    
    for(i=0; i<systemd_fds; ++i)
        set_nonblock(listen_fds_start+i, 1);
#else
    systemd_fds=0; 
    listen_fds_start=3; 
#endif
    
    if(ssl_init()) 
        fatal("STR");
    if(sthreads_init()) 
        fatal("STR");
    options_defaults();
    options_apply();
#ifndef USE_FORK
    get_limits(); 
#endif
    fds=s_poll_alloc();
    if(pipe_init(signal_pipe, "STR"))
        fatal("STR"
            "STR");
    if(pipe_init(terminate_pipe, "STR"))
        fatal("STR"
            "STR");
    stunnel_info(LOG_NOTICE);
    if(systemd_fds>0)
        s_log(LOG_INFO, "STR",
            systemd_fds);
}