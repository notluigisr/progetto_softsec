PHP_FUNCTION(ldap_parse_reference)
{
	zval *link, *result_entry, *referrals;
	ldap_linkdata *ld;
	ldap_resultentry *resultentry;
	char **lreferrals, **refp;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "STR", &link, &result_entry, &referrals) != SUCCESS) {
		return;
	}

	ZEND_FETCH_RESOURCE(ld, ldap_linkdata *, &link, -1, "STR", le_link);
	ZEND_FETCH_RESOURCE(resultentry, ldap_resultentry *, &result_entry, -1, "STR", le_result_entry);

	if (ldap_parse_reference(ld->link, resultentry->data, &lreferrals, NULL , 0) != LDAP_SUCCESS) {
		RETURN_FALSE;
	}

	zval_dtor(referrals);
	array_init(referrals);
	if (lreferrals != NULL) {
		refp = lreferrals;
		while (*refp) {
			add_next_index_string(referrals, *refp, 1);
			refp++;
		}
		ldap_memvfree((void**)lreferrals);
	}
	RETURN_TRUE;
}