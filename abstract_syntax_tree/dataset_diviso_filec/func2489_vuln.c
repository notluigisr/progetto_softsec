_PUBLIC_ enum ndr_err_code ndr_push_nbt_string(struct ndr_push *ndr, int ndr_flags, const char *s)
{
	if (!(ndr_flags & NDR_SCALARS)) {
		return NDR_ERR_SUCCESS;
	}

	while (s && *s) {
		enum ndr_err_code ndr_err;
		char *compname;
		size_t complen;
		uint32_t offset;

		
		ndr_err = ndr_token_retrieve_cmp_fn(&ndr->nbt_string_list, s, &offset, (comparison_fn_t)strcmp, false);
		if (NDR_ERR_CODE_IS_SUCCESS(ndr_err)) {
			uint8_t b[2];

			if (offset > 0x3FFF) {
				return ndr_push_error(ndr, NDR_ERR_STRING,
						      "STR",
						      offset, offset);
			}

			b[0] = 0xC0 | (offset>>8);
			b[1] = (offset & 0xFF);

			return ndr_push_bytes(ndr, b, 2);
		}

		complen = strcspn(s, "STR");

		
		if (complen > 0x3F) {
			return ndr_push_error(ndr, NDR_ERR_STRING,
					      "STR",
					      (unsigned)complen, (unsigned)complen);
		}

		if (s[complen] == '.' && s[complen+1] == '\0') {
			complen++;
		}

		compname = talloc_asprintf(ndr, "STR",
						(unsigned char)complen,
						(unsigned char)complen,
						(unsigned char)complen, s);
		NDR_ERR_HAVE_NO_MEMORY(compname);

		
		NDR_CHECK(ndr_token_store(ndr, &ndr->nbt_string_list, s, ndr->offset));

		
		NDR_CHECK(ndr_push_bytes(ndr, (const uint8_t *)compname, complen+1));
		talloc_free(compname);

		s += complen;
		if (*s == '.') s++;
	}

	
	return ndr_push_bytes(ndr, (const uint8_t *)"", 1);
}