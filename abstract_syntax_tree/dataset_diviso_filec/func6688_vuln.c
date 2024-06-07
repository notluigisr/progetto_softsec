static int nc_dns(ASN1_IA5STRING *dns, ASN1_IA5STRING *base)
{
    char *baseptr = (char *)base->data;
    char *dnsptr = (char *)dns->data;
    
    if (!*baseptr)
        return X509_V_OK;
    
    if (dns->length > base->length) {
        dnsptr += dns->length - base->length;
        if (*baseptr != '.' && dnsptr[-1] != '.')
            return X509_V_ERR_PERMITTED_VIOLATION;
    }

    if (ia5casecmp(baseptr, dnsptr))
        return X509_V_ERR_PERMITTED_VIOLATION;

    return X509_V_OK;

}