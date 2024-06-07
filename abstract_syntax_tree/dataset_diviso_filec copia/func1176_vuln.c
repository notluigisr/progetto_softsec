static int ps_files_valid_key(const char *key)
{
	size_t len;
	const char *p;
	char c;
	int ret = 1;

	for (p = key; (c = *p); p++) {
		
		if (!((c >= 'a' && c <= 'z')
				|| (c >= 'A' && c <= 'Z')
				|| (c >= '0' && c <= '9')
				|| c == ','
				|| c == '-')) {
			ret = 0;
			break;
		}
	}

	len = p - key;

	
	if (len == 0 || len > 128) {
		ret = 0;
	}

	return ret;
}