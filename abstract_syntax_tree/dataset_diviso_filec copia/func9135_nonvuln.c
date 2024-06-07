void print_client_CA_list(const STACK_OF(X509_NAME) *ca_dn) {
    char *ca_name;
    int n, i;

    if(!ca_dn) {
        s_log(LOG_INFO, "STR");
        return;
    }
    n=sk_X509_NAME_num(ca_dn);
    if(n==0) {
        s_log(LOG_INFO, "STR");
        return;
    }
    for(i=0; i<n; ++i) {
        ca_name=X509_NAME2text(sk_X509_NAME_value(ca_dn, i));
        s_log(LOG_INFO, "STR", ca_name);
        str_free(ca_name);
    }
}