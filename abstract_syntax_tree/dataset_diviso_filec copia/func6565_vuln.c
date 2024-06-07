static void init_sasl_conn(conn *c) {
    assert(c);
    
    if (!settings.sasl)
        return;

    if (!c->sasl_conn) {
        int result=sasl_server_new("STR",
                                   NULL,
                                   my_sasl_hostname[0] ? my_sasl_hostname : NULL,
                                   NULL, NULL,
                                   NULL, 0, &c->sasl_conn);
        if (result != SASL_OK) {
            if (settings.verbose) {
                fprintf(stderr, "STR");
            }
            c->sasl_conn = NULL;
        }
    }
}