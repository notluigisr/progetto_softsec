static krb5_error_code hdb_samba4_create(krb5_context context, struct HDB **db, const char *arg)
{
	NTSTATUS nt_status;
	void *ptr = NULL;
	struct samba_kdc_base_context *base_ctx = NULL;

	if (sscanf(arg, "STR", &ptr) != 1) {
		return EINVAL;
	}

	base_ctx = talloc_get_type_abort(ptr, struct samba_kdc_base_context);

	
	nt_status = hdb_samba4_create_kdc(base_ctx, context, db);

	if (NT_STATUS_IS_OK(nt_status)) {
		return 0;
	} else if (NT_STATUS_EQUAL(nt_status, NT_STATUS_ERROR_DS_INCOMPATIBLE_VERSION)) {
		return EINVAL;
	} else if (NT_STATUS_EQUAL(nt_status, NT_STATUS_CANT_ACCESS_DOMAIN_INFO)) {
		
		krb5_set_error_message(context, EINVAL, "STR"));
	} else {
		krb5_set_error_message(context, EINVAL, "STR", get_friendly_nt_error_msg(nt_status), nt_errstr(nt_status));
	}

	return EINVAL;
}