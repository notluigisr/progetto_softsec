sentinel_get_keytag(char* start, uint16_t* keytag) {
	char* keytag_str;
	char* e = NULL;
	keytag_str = calloc(1, SENTINEL_KEYTAG_LEN + 1 );
	if(!keytag_str)
		return 0;
	memmove(keytag_str, start, SENTINEL_KEYTAG_LEN);
	keytag_str[SENTINEL_KEYTAG_LEN] = '\0';
	*keytag = (uint16_t)strtol(keytag_str, &e, 10);
	if(!e || *e != '\0') {
		free(keytag_str);
		return 0;
	}
	free(keytag_str);
	return 1;
}