unsigned char *next_protos_parse(unsigned short *outlen, const char *in)
	{
	size_t len;
	unsigned char *out;
	size_t i, start = 0;

	len = strlen(in);
	if (len > 65535)
		return NULL;

	out = OPENSSL_malloc(strlen(in) + 1);
	if (!out)
		return NULL;

	for (i = 0; i <= len; ++i)
		{
		if (i == len || in[i] == ',')
			{
			if (i - start > 255)
				{
				OPENSSL_free(out);
				return NULL;
				}
			out[start] = i - start;
			start = i + 1;
			}
		else
			out[i+1] = in[i];
		}

	*outlen = len + 1;
	return out;
	}