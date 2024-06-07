authentic_manage_sdo_encode(struct sc_card *card, struct sc_authentic_sdo *sdo, unsigned long cmd,
			unsigned char **out, size_t *out_len)
{
	struct sc_context *ctx = card->ctx;
	unsigned char *data = NULL;
	size_t data_len = 0;
	unsigned char data_tag = AUTHENTIC_TAG_DOCP;
	int rv;

	LOG_FUNC_CALLED(ctx);
	sc_log(ctx, "STR", cmd, sdo->docp.mech, sdo->docp.id);

	if (!out || !out_len)
		LOG_TEST_RET(ctx, SC_ERROR_INVALID_ARGUMENTS, "STR");

	rv = authentic_update_blob(ctx, AUTHENTIC_TAG_DOCP_MECH, &sdo->docp.mech, sizeof(sdo->docp.mech),
			&data, &data_len);
	LOG_TEST_RET(ctx, rv, "STR");

	rv = authentic_update_blob(ctx, AUTHENTIC_TAG_DOCP_ID, &sdo->docp.id, sizeof(sdo->docp.id),
			&data, &data_len);
	LOG_TEST_RET(ctx, rv, "STR");

	if (cmd == SC_CARDCTL_AUTHENTIC_SDO_CREATE)   {
		rv = authentic_update_blob(ctx, AUTHENTIC_TAG_DOCP_ACLS, sdo->docp.acl_data, sdo->docp.acl_data_len,
				&data, &data_len);
		LOG_TEST_RET(ctx, rv, "STR");

		if (sdo->docp.security_parameter)  {
			rv = authentic_update_blob(ctx, AUTHENTIC_TAG_DOCP_SCP,
					&sdo->docp.security_parameter, sizeof(sdo->docp.security_parameter),
					&data, &data_len);
			LOG_TEST_RET(ctx, rv, "STR");
		}
		if (sdo->docp.usage_counter[0] || sdo->docp.usage_counter[1])  {
			rv = authentic_update_blob(ctx, AUTHENTIC_TAG_DOCP_USAGE_COUNTER,
					sdo->docp.usage_counter, sizeof(sdo->docp.usage_counter),
					&data, &data_len);
			LOG_TEST_RET(ctx, rv, "STR");
		}
	}
	else if (cmd == SC_CARDCTL_AUTHENTIC_SDO_STORE)   {
		if (sdo->docp.mech == AUTHENTIC_MECH_CRYPTO_RSA1024
				|| sdo->docp.mech == AUTHENTIC_MECH_CRYPTO_RSA1280
				|| sdo->docp.mech == AUTHENTIC_MECH_CRYPTO_RSA1536
				|| sdo->docp.mech == AUTHENTIC_MECH_CRYPTO_RSA1792
				|| sdo->docp.mech == AUTHENTIC_MECH_CRYPTO_RSA2048)   {
			rv = authentic_manage_sdo_encode_prvkey(card, sdo->data.prvkey, &data, &data_len);
			LOG_TEST_RET(ctx, rv, "STR");
		}
		else  {
			LOG_TEST_RET(ctx, SC_ERROR_NOT_SUPPORTED, "STR");
		}
	}
	else if (cmd == SC_CARDCTL_AUTHENTIC_SDO_GENERATE)   {
		if (sdo->data.prvkey)   {
		        rv = authentic_update_blob(ctx, AUTHENTIC_TAG_RSA_PUBLIC_EXPONENT,
					sdo->data.prvkey->u.rsa.exponent.data, sdo->data.prvkey->u.rsa.exponent.len,
					&data, &data_len);
		        LOG_TEST_RET(ctx, rv, "STR");
		}

		data_tag = AUTHENTIC_TAG_RSA_GENERATE_DATA;
	}
	else if (cmd != SC_CARDCTL_AUTHENTIC_SDO_DELETE)   {
		LOG_TEST_RET(ctx, SC_ERROR_INVALID_DATA, "STR");
	}

	rv = authentic_update_blob(ctx, data_tag, data, data_len, out, out_len);
	LOG_TEST_RET(ctx, rv, "STR");

	free(data);

	sc_log_hex(ctx, "STR", *out, *out_len);
	LOG_FUNC_RETURN(ctx, rv);
}