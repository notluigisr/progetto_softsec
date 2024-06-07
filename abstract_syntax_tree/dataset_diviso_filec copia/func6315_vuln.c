apr_status_t h2_slave_run_pre_connection(conn_rec *slave, apr_socket_t *csd)
{
    if (slave->keepalives == 0) {
        
        slave->keepalives = 1;
        
        slave->keepalive = AP_CONN_CLOSE;
        return ap_run_pre_connection(slave, csd);
    }
    return APR_SUCCESS;
}