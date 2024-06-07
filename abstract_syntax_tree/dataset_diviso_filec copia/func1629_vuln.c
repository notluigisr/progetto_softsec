R_API char *r_socket_http_get(const char *url, int *code, int *rlen) {
	char *curl_env = r_sys_getenv ("STR");
	if (curl_env && *curl_env) {
		char *encoded_url = r_str_escape (url);
		char *res = r_sys_cmd_strf ("STR", encoded_url);
		free (encoded_url);
		if (res) {
			if (code) {
				*code = 200;
			}
			if (rlen) {
				*rlen = strlen (res);
			}
		}
		free (curl_env);
		return res;
	}
	free (curl_env);
	RSocket *s;
	int ssl = r_str_startswith (url, "STR");
	char *response, *host, *path, *port = "STR";
	char *uri = strdup (url);
	if (!uri) {
		return NULL;
	}

	if (code) {
		*code = 0;
	}
	if (rlen) {
		*rlen = 0;
	}
	host = strstr (uri, "STR");
	if (!host) {
		free (uri);
		eprintf ("STR");
		return NULL;
	}
	host += 3;
	port = strchr (host, ':');
	if (!port) {
		port = ssl? "STR";
		path = host;
	} else {
		*port++ = 0;
		path = port;
	}
	path = strchr (path, '/');
	if (!path) {
		path = "";
	} else {
		*path++ = 0;
	}
	s = r_socket_new (ssl);
	if (!s) {
		eprintf ("STR");
		free (uri);
		return NULL;
	}
	if (r_socket_connect_tcp (s, host, port, 0)) {
		r_socket_printf (s,
				"STR"
				"STR"
				"STR"
				"STR"
				"STR", path, host, port);
		response = r_socket_http_answer (s, code, rlen);
	} else {
		eprintf ("STR", host, port);
		response = NULL;
	}
	free (uri);
	r_socket_free (s);
	return response;
}