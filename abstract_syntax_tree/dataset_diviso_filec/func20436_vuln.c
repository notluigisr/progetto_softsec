static int obj_trust(int id, X509 *x, int flags)
{
    X509_CERT_AUX *ax = x->aux;
    int i;

    if (!ax)
        return X509_TRUST_UNTRUSTED;
    if (ax->reject) {
        for (i = 0; i < sk_ASN1_OBJECT_num(ax->reject); i++) {
            ASN1_OBJECT *obj = sk_ASN1_OBJECT_value(ax->reject, i);
            int nid = OBJ_obj2nid(obj);

            if (nid == id || nid == NID_anyExtendedKeyUsage)
                return X509_TRUST_REJECTED;
        }
    }
    if (ax->trust) {
        for (i = 0; i < sk_ASN1_OBJECT_num(ax->trust); i++) {
            ASN1_OBJECT *obj = sk_ASN1_OBJECT_value(ax->trust, i);
            int nid = OBJ_obj2nid(obj);

            if (nid == id || nid == NID_anyExtendedKeyUsage)
                return X509_TRUST_TRUSTED;
        }
        
        return X509_TRUST_REJECTED;
    }
    return X509_TRUST_UNTRUSTED;
}