static int piv_get_challenge(sc_card_t *card, u8 *rnd, size_t len)
{
	
	u8 sbuf[] = {0x7c, 0x02, 0x81, 0x00};
	u8 *rbuf = NULL;
	const u8 *p;
	size_t rbuf_len = 0, out_len = 0;
	int r;
	unsigned int tag, cla;

	LOG_FUNC_CALLED(card->ctx);

	
	r = piv_general_io(card, 0x87, 0x00, 0x9B, sbuf, sizeof sbuf, &rbuf, &rbuf_len);
	LOG_TEST_GOTO_ERR(card->ctx, r, "STR");

	p = rbuf;
	r = sc_asn1_read_tag(&p, rbuf_len, &cla, &tag, &out_len);
	if (r < 0 || (cla|tag) != 0x7C) {
		LOG_TEST_GOTO_ERR(card->ctx, SC_ERROR_INVALID_DATA, "STR");
	}

	rbuf_len = out_len;
	r = sc_asn1_read_tag(&p, rbuf_len, &cla, &tag, &out_len);
	if (r < 0 || (cla|tag) != 0x81) {
		LOG_TEST_GOTO_ERR(card->ctx, SC_ERROR_INVALID_DATA, "STR");
	}

	if (len < out_len) {
		out_len = len;
	}
	memcpy(rnd, p, out_len);

	r = (int) out_len;

err:
	free(rbuf);

	LOG_FUNC_RETURN(card->ctx, r);

}