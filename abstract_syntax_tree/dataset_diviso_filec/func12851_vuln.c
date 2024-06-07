static bool authenticated(conn *c) {
    assert(settings.sasl);
    bool rv = false;

    switch (c->cmd) {
    case PROTOCOL_BINARY_CMD_SASL_LIST_MECHS: 
    case PROTOCOL_BINARY_CMD_SASL_AUTH:       
    case PROTOCOL_BINARY_CMD_SASL_STEP:       
    case PROTOCOL_BINARY_CMD_VERSION:         
        rv = true;
        break;
    default:
        if (c->sasl_conn) {
            const void *uname = NULL;
            sasl_getprop(c->sasl_conn, SASL_USERNAME, &uname);
            rv = uname != NULL;
        }
    }

    if (settings.verbose > 1) {
        fprintf(stderr, "STR",
                c->cmd, rv ? "STR");
    }

    return rv;
}