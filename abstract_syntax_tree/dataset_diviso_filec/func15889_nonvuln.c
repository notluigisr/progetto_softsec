int gnutls_x509_crt_to_xml(gnutls_x509_crt_t cert, gnutls_datum_t * res,
			   int detail)
{
    int result;

    res->data = NULL;
    res->size = 0;

    result = _gnutls_asn1_get_structure_xml(cert->cert, res, detail);
    if (result < 0) {
	gnutls_assert();
	return result;
    }

    return 0;
}