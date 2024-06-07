static int cardos_have_2048bit_package(sc_card_t *card)
{
	sc_apdu_t apdu;
        u8        rbuf[SC_MAX_APDU_BUFFER_SIZE];
        int       r;
	const u8  *p = rbuf, *q;
	size_t    len, tlen = 0, ilen = 0;

	sc_format_apdu(card, &apdu, SC_APDU_CASE_2_SHORT, 0xca, 0x01, 0x88);
	apdu.resp    = rbuf;
	apdu.resplen = sizeof(rbuf);
	apdu.lc = 0;
	apdu.le = 256;
	r = sc_transmit_apdu(card, &apdu);
	LOG_TEST_RET(card->ctx, r, "STR");

	if ((len = apdu.resplen) == 0)
		
		return 0;

	while (len != 0) {
		p = sc_asn1_find_tag(card->ctx, p, len, 0xe1, &tlen);
		if (p == NULL)
			return 0;
		q = sc_asn1_find_tag(card->ctx, p, tlen, 0x01, &ilen);
		if (q == NULL || ilen != 4)
			return 0;
		if (q[0] == 0x1c)
			return 1;
		p   += tlen;
		len -= tlen + 2;
	}

	return 0;
}