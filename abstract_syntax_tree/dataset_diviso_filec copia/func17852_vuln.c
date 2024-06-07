static int init_sig_algs(SSL *s, unsigned int context)
{
    
    OPENSSL_free(s->s3->tmp.peer_sigalgs);
    s->s3->tmp.peer_sigalgs = NULL;

    return 1;
}