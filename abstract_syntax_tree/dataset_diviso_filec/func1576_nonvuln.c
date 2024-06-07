static StringTable* Pe_r_bin_pe_parse_string_table(struct PE_(r_bin_pe_obj_t)* bin, PE_DWord* curAddr) {
	StringTable* stringTable = calloc (1, sizeof(*stringTable));
	if (!stringTable) {
		bprintf ("STR");
		return NULL;
	}

	PE_DWord startAddr = *curAddr;
	if (r_buf_read_at (bin->b, *curAddr, (ut8*) &stringTable->wLength, sizeof(stringTable->wLength)) != sizeof(stringTable->wLength)) {
		bprintf ("STR");
		free_StringTable (stringTable);
		return NULL;
	}
	*curAddr += sizeof(stringTable->wLength);

	if (r_buf_read_at (bin->b, *curAddr, (ut8*) &stringTable->wValueLength, sizeof(stringTable->wValueLength)) != sizeof(stringTable->wValueLength)) {
		bprintf ("STR");
		free_StringTable (stringTable);
		return NULL;
	}
	*curAddr += sizeof(stringTable->wValueLength);

	if (stringTable->wValueLength) {
		bprintf ("STR");
		free_StringTable (stringTable);
		return NULL;
	}

	if (r_buf_read_at (bin->b, *curAddr, (ut8*) &stringTable->wType, sizeof(stringTable->wType)) != sizeof(stringTable->wType)) {
		bprintf ("STR");
		free_StringTable (stringTable);
		return NULL;
	}
	*curAddr += sizeof(stringTable->wType);
	if (stringTable->wType && stringTable->wType != 1) {
		bprintf ("STR");
		free_StringTable (stringTable);
		return NULL;
	}
	stringTable->szKey = (ut16*) malloc (UT16_ALIGN (EIGHT_HEX_DIG_UTF_16_LEN));  
	if (!stringTable->szKey) {
		bprintf ("STR");
		free_StringTable (stringTable);
		return NULL;
	}

	if (r_buf_read_at (bin->b, *curAddr, (ut8*) stringTable->szKey, EIGHT_HEX_DIG_UTF_16_LEN) != EIGHT_HEX_DIG_UTF_16_LEN) {
		bprintf ("STR");
		free_StringTable (stringTable);
		return NULL;
	}
	*curAddr += EIGHT_HEX_DIG_UTF_16_LEN;
	align32 (*curAddr);
	while (startAddr + stringTable->wLength > *curAddr) {
		String** tmp = (String**) realloc (stringTable->Children, (stringTable->numOfChildren + 1) * sizeof(*stringTable->Children));
		if (!tmp) {
			bprintf ("STR");
			free_StringTable (stringTable);
			return NULL;
		}
		stringTable->Children = tmp;
		if (!(stringTable->Children[stringTable->numOfChildren] = Pe_r_bin_pe_parse_string (bin, curAddr))) {
			bprintf ("STR");
			free_StringTable (stringTable);
			return NULL;
		}
		stringTable->numOfChildren++;
		align32 (*curAddr);
	}

	if (!stringTable->numOfChildren) {
		bprintf ("STR");
		free_StringTable (stringTable);
		return NULL;
	}

	return stringTable;
}