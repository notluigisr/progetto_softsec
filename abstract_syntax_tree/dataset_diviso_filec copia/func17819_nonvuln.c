int pgp_logout(struct sc_card *card)
{
	int r = SC_SUCCESS;
	struct pgp_priv_data *priv = DRVDATA(card);

	LOG_FUNC_CALLED(card->ctx);

	if (priv->bcd_version >= OPENPGP_CARD_3_1) {
		unsigned char pin_reference;
		for (pin_reference = 0x81; pin_reference <= 0x83; pin_reference++) {
			int tmp = iso7816_logout(card, pin_reference);
			if (r == SC_SUCCESS) {
				r = tmp;
			}
		}
	} else {
		sc_path_t path;
		sc_file_t *file = NULL;

		
		sc_format_path("STR", &path);
		path.type = SC_PATH_TYPE_DF_NAME;
		r = iso_ops->select_file(card, &path, &file);
		sc_file_free(file);
	}

	LOG_FUNC_RETURN(card->ctx, r);
}