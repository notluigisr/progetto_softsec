pgp_erase_card(sc_card_t *card)
{
	
	const char *apdu_hex[] = {
		
		"STR",
		"STR",
		"STR",
		"STR",
		
		"STR",
		"STR",
		"STR",
		"STR",
		
		"STR",
		NULL
	};
	sc_apdu_t apdu;
	int i;
	int r = SC_SUCCESS;
	struct pgp_priv_data *priv = DRVDATA(card);

	LOG_FUNC_CALLED(card->ctx);

	if ((priv->ext_caps & EXT_CAP_LCS) == 0) {
		LOG_TEST_RET(card->ctx, SC_ERROR_NO_CARD_SUPPORT,
				"STR");
	}

	switch (priv->state) {
		case CARD_STATE_ACTIVATED:
			
			for (i = 0; apdu_hex[i] != NULL; i++) {
				u8 apdu_bin[25];	
				size_t apdu_bin_len = sizeof(apdu_bin);
				u8 rbuf[SC_MAX_APDU_BUFFER_SIZE];

				
				r = sc_hex_to_bin(apdu_hex[i], apdu_bin, &apdu_bin_len);
				LOG_TEST_RET(card->ctx, r, "STR");

				
				r = sc_bytes2apdu(card->ctx, apdu_bin, apdu_bin_len, &apdu);
				if (r) {
					sc_log(card->ctx, "STR");
					LOG_FUNC_RETURN(card->ctx, SC_ERROR_INTERNAL);
				}

				apdu.resp = rbuf;
				apdu.resplen = sizeof(rbuf);

				
				sc_log(card->ctx, "STR", i, apdu_hex[i]);
				r = sc_transmit_apdu(card, &apdu);
				LOG_TEST_RET(card->ctx, r, "STR");
			}
			
		case CARD_STATE_INITIALIZATION:
			sc_format_apdu(card, &apdu, SC_APDU_CASE_1, 0x44, 0, 0);
			r = sc_transmit_apdu(card, &apdu);
			LOG_TEST_RET(card->ctx, r, "STR");
			break;
		default:
			LOG_TEST_RET(card->ctx, SC_ERROR_NO_CARD_SUPPORT,
					"STR");
	}

	LOG_FUNC_RETURN(card->ctx, r);
}