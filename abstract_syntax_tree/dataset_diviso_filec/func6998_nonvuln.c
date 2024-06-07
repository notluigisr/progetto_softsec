gpk_select(sc_card_t *card, int kind,
		const u8 *buf, size_t buflen,
		sc_file_t **file)
{
	struct gpk_private_data *priv = DRVDATA(card);
	sc_apdu_t	apdu;
	u8		resbuf[256];
	int		r;

	
	if (kind == GPK_SEL_MF || kind == GPK_SEL_DF) {
		memset(priv->key, 0, sizeof(priv->key));
		priv->key_set = 0;
	}

	
	memset(&apdu, 0, sizeof(apdu));
	apdu.cla = 0x00;
	apdu.cse = SC_APDU_CASE_3_SHORT;
	apdu.ins = 0xA4;
	apdu.p1 = kind;
	apdu.p2 = 0;
	apdu.data = buf;
	apdu.datalen = buflen;
	apdu.lc = apdu.datalen;

	if (file) {
		apdu.cse = SC_APDU_CASE_4_SHORT;
		apdu.resp = resbuf;
		apdu.resplen = sizeof(resbuf);
		apdu.le = sizeof(resbuf);
	}

	r = sc_transmit_apdu(card, &apdu);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "STR");
	r = sc_check_sw(card, apdu.sw1, apdu.sw2);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "STR");

	
	if (kind == GPK_SEL_AID) {
		card->cache.current_path.len = 0;
	}

	if (file == NULL)
		return 0;
	*file = sc_file_new();

	r = gpk_parse_fileinfo(card, apdu.resp, apdu.resplen, *file);
	if (r < 0) {
		sc_file_free(*file);
		*file = NULL;
	}
	return r;
}