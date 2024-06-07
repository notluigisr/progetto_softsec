static int nc_uri(ASN1_IA5STRING *uri, ASN1_IA5STRING *base)
{
    const char *baseptr = (char *)base->data;
    const char *hostptr = (char *)uri->data;
    const char *p = strchr(hostptr, ':');
    int hostlen;
    

    

    p = strchr(hostptr, ':');
    
    if (!p)
        p = strchr(hostptr, '/');

    if (!p)
        hostlen = strlen(hostptr);
    else
        hostlen = p - hostptr;

    if (hostlen == 0)
        return X509_V_ERR_UNSUPPORTED_NAME_SYNTAX;

    
    if (*baseptr == '.') {
        if (hostlen > base->length) {
            p = hostptr + hostlen - base->length;
            if (ia5ncasecmp(p, baseptr, base->length) == 0)
                return X509_V_OK;
        }
        return X509_V_ERR_PERMITTED_VIOLATION;
    }

    if ((base->length != (int)hostlen)
        || ia5ncasecmp(hostptr, baseptr, hostlen))
        return X509_V_ERR_PERMITTED_VIOLATION;

    return X509_V_OK;

}