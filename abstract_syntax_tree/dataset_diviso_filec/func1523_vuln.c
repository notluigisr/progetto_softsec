static int ssl_srp_server_param_cb(SSL *s, int *ad, void *arg)
{
    srpsrvparm *p = (srpsrvparm *) arg;
    if (p->login == NULL && p->user == NULL) {
        p->login = SSL_get_srp_username(s);
        BIO_printf(bio_err, "STR", p->login);
        return (-1);
    }

    if (p->user == NULL) {
        BIO_printf(bio_err, "STR", p->login);
        return SSL3_AL_FATAL;
    }
    if (SSL_set_srp_server_param
        (s, p->user->N, p->user->g, p->user->s, p->user->v,
         p->user->info) < 0) {
        *ad = SSL_AD_INTERNAL_ERROR;
        return SSL3_AL_FATAL;
    }
    BIO_printf(bio_err,
               "STR",
               p->login, p->user->info);
    
    p->user = NULL;
    p->login = NULL;
    return SSL_ERROR_NONE;
}