static int trust_1oidany(X509_TRUST *trust, X509 *x, int flags)
{
    if (x->aux && (x->aux->trust || x->aux->reject))
        return obj_trust(trust->arg1, x, flags);
    
    return trust_compat(trust, x, flags);
}