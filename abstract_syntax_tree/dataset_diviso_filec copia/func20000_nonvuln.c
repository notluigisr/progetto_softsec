ASN1_TYPE *PKCS7_get_attribute(PKCS7_SIGNER_INFO *si, int nid)
{
    return get_attribute(si->unauth_attr, nid);
}