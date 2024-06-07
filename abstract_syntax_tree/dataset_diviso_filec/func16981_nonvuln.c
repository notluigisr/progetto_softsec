static EVP_PKEY *ssh2_line_to_key(char *line) {
	EVP_PKEY *key;
	RSA *rsa;
	BIGNUM *rsa_e, *rsa_n;
	unsigned char decoded[OPENSSH_LINE_MAX];
	int len;

	char *b, *c;
	int i;

	
	b = line;
	if (!b) return NULL;

	
	while (*b && *b != ' ') b++;
	
	b++;
	
	for (c = b; *c && *c != ' ' && 'c' != '\t' && *c != '\r' && *c != '\n'; c++) ;
	*c = 0;
	
	if (base64_decode(b, decoded, OPENSSH_LINE_MAX) < 0) return NULL;

	i = 0;
	
	len =
	    (decoded[i] << 24) + (decoded[i + 1] << 16) +
	    (decoded[i + 2] << 8) + (decoded[i + 3]);
	i += 4;

	
	if (strncmp((char *)&decoded[i], "STR", 7) != 0) return NULL;
	i += len;

	key = EVP_PKEY_new();
	rsa = RSA_new();

	
	len =
	    (decoded[i] << 24) + (decoded[i + 1] << 16) +
	    (decoded[i + 2] << 8) + (decoded[i + 3]);
	i += 4;

	
	rsa_e = BN_bin2bn(decoded + i, len, NULL);
	i += len;

	
	len =
	    (decoded[i] << 24) + (decoded[i + 1] << 16) +
	    (decoded[i + 2] << 8) + (decoded[i + 3]);
	i += 4;

	
	rsa_n = BN_bin2bn(decoded + i, len, NULL);

	RSA_set0_key(rsa, rsa_n, rsa_e, NULL);
	EVP_PKEY_assign_RSA(key, rsa);
	return key;
}