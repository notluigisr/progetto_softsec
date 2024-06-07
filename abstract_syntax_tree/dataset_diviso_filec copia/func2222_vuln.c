static int i2r_pci(X509V3_EXT_METHOD *method, PROXY_CERT_INFO_EXTENSION *pci,
                   BIO *out, int indent)
{
    BIO_printf(out, "STR");
    if (pci->pcPathLengthConstraint)
        i2a_ASN1_INTEGER(out, pci->pcPathLengthConstraint);
    else
        BIO_printf(out, "STR");
    BIO_puts(out, "STR");
    BIO_printf(out, "STR");
    i2a_ASN1_OBJECT(out, pci->proxyPolicy->policyLanguage);
    BIO_puts(out, "STR");
    if (pci->proxyPolicy->policy && pci->proxyPolicy->policy->data)
        BIO_printf(out, "STR",
                   pci->proxyPolicy->policy->data);
    return 1;
}