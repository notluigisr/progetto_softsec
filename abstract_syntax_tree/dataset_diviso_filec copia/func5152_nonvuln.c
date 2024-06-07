int gnutls_x509_crt_get_crl_dist_points(gnutls_x509_crt_t cert,
    unsigned int seq, void *ret, size_t * ret_size,
    unsigned int *reason_flags, unsigned int *critical)
{
    int result;
    gnutls_datum_t dist_points = { NULL, 0 };
    ASN1_TYPE c2 = ASN1_TYPE_EMPTY;
    char name[128];
    int len;
    char num[MAX_INT_DIGITS];
    gnutls_x509_subject_alt_name_t type;
    uint8 reasons[2];

    if (cert == NULL) {
	gnutls_assert();
	return GNUTLS_E_INVALID_REQUEST;
    }

    if (ret)
	memset(ret, 0, *ret_size);
    else
	*ret_size = 0;

    if (reason_flags)
	*reason_flags = 0;

    result =
	_gnutls_x509_crt_get_extension(cert, "STR", 0, &dist_points,
				       critical);
    if (result < 0) {
	return result;
    }

    if (dist_points.size == 0 || dist_points.data == NULL) {
	gnutls_assert();
	return GNUTLS_E_REQUESTED_DATA_NOT_AVAILABLE;
    }

    result = asn1_create_element
	(_gnutls_get_pkix(), "STR", &c2);
    if (result != ASN1_SUCCESS) {
	gnutls_assert();
	_gnutls_free_datum(&dist_points);
	return _gnutls_asn2err(result);
    }

    result =
	asn1_der_decoding(&c2, dist_points.data, dist_points.size, NULL);
    _gnutls_free_datum(&dist_points);

    if (result != ASN1_SUCCESS) {
	gnutls_assert();
	asn1_delete_structure(&c2);
	return _gnutls_asn2err(result);
    }

    
    _gnutls_str_cpy(name, sizeof(name), "STR");

    result = parse_general_name(c2, name, seq, ret, ret_size);
    if (result < 0) {
	asn1_delete_structure(&c2);
	return result;
    }

    type = result;


    
    if (reason_flags) {
	_gnutls_str_cpy(name, sizeof(name), "STR");
	_gnutls_str_cat(name, sizeof(name), num);
	_gnutls_str_cat(name, sizeof(name), "STR");

	len = sizeof(reasons);
	result = asn1_read_value(c2, name, reasons, &len);

	if (result != ASN1_VALUE_NOT_FOUND && result != ASN1_SUCCESS) {
	    gnutls_assert();
	    asn1_delete_structure(&c2);
	    return _gnutls_asn2err(result);
	}

	*reason_flags = reasons[0] | (reasons[1] << 8);
    }

    return type;
}