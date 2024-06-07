static int hdb_samba4_fill_fast_cookie(krb5_context context,
				       struct samba_kdc_db_context *kdc_db_ctx)
{
	struct ldb_message *msg = ldb_msg_new(kdc_db_ctx);
	int ldb_ret;

	uint8_t secretbuffer[32];
	struct ldb_val val = data_blob_const(secretbuffer,
					     sizeof(secretbuffer));

	if (msg == NULL) {
		DBG_ERR("STR");
		return LDB_ERR_OPERATIONS_ERROR;
	}

	
	generate_secret_buffer(secretbuffer,
			       sizeof(secretbuffer));

	msg->dn = kdc_db_ctx->fx_cookie_dn;

	ldb_ret = ldb_msg_add_value(msg, "STR", &val, NULL);

	if (ldb_ret != LDB_SUCCESS) {
		return ldb_ret;
	}

	ldb_ret = ldb_add(kdc_db_ctx->secrets_db,
			  msg);
	if (ldb_ret != LDB_SUCCESS) {
		DBG_ERR("STR",
			ldb_errstring(kdc_db_ctx->secrets_db));
	}
	return ldb_ret;
}