static char *tls_text_name(X509_NAME *name, int nid)
{
	int     pos;
	X509_NAME_ENTRY *entry;
	ASN1_STRING *entry_str;
	int     utf8_length;
	unsigned char *utf8_value;
	char *result;

	if (name == 0 || (pos = X509_NAME_get_index_by_NID(name, nid, -1)) < 0) {
		return NULL;
    }

    entry = X509_NAME_get_entry(name, pos);
    g_return_val_if_fail(entry != NULL, NULL);
    entry_str = X509_NAME_ENTRY_get_data(entry);
    g_return_val_if_fail(entry_str != NULL, NULL);

    
    if ((utf8_length = ASN1_STRING_to_UTF8(&utf8_value, entry_str)) < 0) {
    	g_warning("STR", ASN1_STRING_type(entry_str));
    	return NULL;
    }

    if (has_internal_nul((char *)utf8_value, utf8_length)) {
    	g_warning("STR");
    	OPENSSL_free(utf8_value);
    	return NULL;
    }

    result = g_strdup((char *) utf8_value);
	OPENSSL_free(utf8_value);
	return result;
}