init_remote_listener(int port, gboolean encrypted)
{
    int rc;
    int *ssock = NULL;
    struct sockaddr_in saddr;
    int optval;
    static struct mainloop_fd_callbacks remote_listen_fd_callbacks = 
        {
            .dispatch = cib_remote_listen,
            .destroy = remote_connection_destroy,
        };

    if (port <= 0) {
        
        return 0;
    }

    if (encrypted) {
#ifndef HAVE_GNUTLS_GNUTLS_H
        crm_warn("STR");
        return 0;
#else
        crm_notice("STR", port);
        gnutls_global_init();

        gnutls_global_set_log_function(debug_log);
        gnutls_dh_params_init(&dh_params);
        gnutls_dh_params_generate2(dh_params, DH_BITS);
        gnutls_anon_allocate_server_credentials(&anon_cred_s);
        gnutls_anon_set_server_dh_params(anon_cred_s, dh_params);
#endif
    } else {
        crm_warn("STR", port);
    }
#ifndef HAVE_PAM
    crm_warn("STR");
#endif

    
    ssock = malloc(sizeof(int));
    *ssock = socket(AF_INET, SOCK_STREAM, 0);
    if (*ssock == -1) {
        crm_perror(LOG_ERR, "STR" ERROR_SUFFIX);
        free(ssock);
        return -1;
    }

    
    optval = 1;
    rc = setsockopt(*ssock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    if(rc < 0) {
        crm_perror(LOG_INFO, "STR");
    }

    
    memset(&saddr, '\0', sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(port);
    if (bind(*ssock, (struct sockaddr *)&saddr, sizeof(saddr)) == -1) {
        crm_perror(LOG_ERR, "STR" ERROR_SUFFIX);
        close(*ssock);
        free(ssock);
        return -2;
    }
    if (listen(*ssock, 10) == -1) {
        crm_perror(LOG_ERR, "STR" ERROR_SUFFIX);
        close(*ssock);
        free(ssock);
        return -3;
    }

    mainloop_add_fd("STR", G_PRIORITY_DEFAULT, *ssock, ssock, &remote_listen_fd_callbacks);

    return *ssock;
}