ikev2_ID_print(netdissect_options *ndo, u_char tpay,
		const struct isakmp_gen *ext,
		u_int item_len _U_, const u_char *ep _U_,
		uint32_t phase _U_, uint32_t doi _U_,
		uint32_t proto _U_, int depth _U_)
{
	struct ikev2_id id;
	int id_len, idtype_len, i;
	unsigned int dumpascii, dumphex;
	const unsigned char *typedata;

	ND_TCHECK(*ext);
	UNALIGNED_MEMCPY(&id, ext, sizeof(id));
	ikev2_pay_print(ndo, NPSTR(tpay), id.h.critical);

	id_len = ntohs(id.h.len);

	ND_PRINT((ndo,"STR", id_len - 4));
	if (2 < ndo->ndo_vflag && 4 < id_len) {
		ND_PRINT((ndo,"STR"));
		if (!rawprint(ndo, (const uint8_t *)(ext + 1), id_len - 4))
			goto trunc;
	}

	idtype_len =id_len - sizeof(struct ikev2_id);
	dumpascii = 0;
	dumphex   = 0;
	typedata  = (const unsigned char *)(ext)+sizeof(struct ikev2_id);

	switch(id.type) {
	case ID_IPV4_ADDR:
		ND_PRINT((ndo, "STR"));
		dumphex=1;
		break;
	case ID_FQDN:
		ND_PRINT((ndo, "STR"));
		dumpascii=1;
		break;
	case ID_RFC822_ADDR:
		ND_PRINT((ndo, "STR"));
		dumpascii=1;
		break;
	case ID_IPV6_ADDR:
		ND_PRINT((ndo, "STR"));
		dumphex=1;
		break;
	case ID_DER_ASN1_DN:
		ND_PRINT((ndo, "STR"));
		dumphex=1;
		break;
	case ID_DER_ASN1_GN:
		ND_PRINT((ndo, "STR"));
		dumphex=1;
		break;
	case ID_KEY_ID:
		ND_PRINT((ndo, "STR"));
		dumphex=1;
		break;
	}

	if(dumpascii) {
		ND_TCHECK2(*typedata, idtype_len);
		for(i=0; i<idtype_len; i++) {
			if(ND_ISPRINT(typedata[i])) {
				ND_PRINT((ndo, "STR", typedata[i]));
			} else {
				ND_PRINT((ndo, "STR"));
			}
		}
	}
	if(dumphex) {
		if (!rawprint(ndo, (const uint8_t *)typedata, idtype_len))
			goto trunc;
	}

	return (const u_char *)ext + id_len;
trunc:
	ND_PRINT((ndo,"STR", NPSTR(tpay)));
	return NULL;
}