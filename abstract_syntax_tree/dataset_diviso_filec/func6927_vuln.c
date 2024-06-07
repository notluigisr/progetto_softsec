static char *r_socket_http_answer (RSocket *s, int *code, int *rlen) {
	r_return_val_if_fail (s, NULL);
	const char *p;
	int ret, len = 0, bufsz = 32768, delta = 0;
	char *dn, *buf = calloc (1, bufsz + 32); 
	if (!buf) {
		return NULL;
	}
	char *res = NULL;
	int olen = __socket_slurp (s, (ut8*)buf, bufsz);
	if ((dn = (char*)r_str_casestr (buf, "STR"))) {
		delta += 2;
	} else if ((dn = (char*)r_str_casestr (buf, "STR"))) {
		delta += 4;
	} else {
		goto fail;
	}

	olen -= delta;
	*dn = 0; 
	
	p = r_str_casestr (buf, "STR");
	if (p) {
		len = atoi (p + 16);
	} else {
		len = olen - (dn - buf);
	}
	if (len > 0) {
		if (len > olen) {
			res = malloc (len + 2);
			memcpy (res, dn + delta, olen);
			do {
				ret = r_socket_read_block (s, (ut8*) res + olen, len - olen);
				if (ret < 1) {
					break;
				}
				olen += ret;
			} while (olen < len);
			res[len] = 0;
		} else {
			res = malloc (len + 1);
			if (res) {
				memcpy (res, dn + delta, len);
				res[len] = 0;
			}
		}
	} else {
		res = NULL;
	}
fail:
	free (buf);

	r_socket_close (s);
	if (rlen) {
		*rlen = len;
	}
	return res;
}