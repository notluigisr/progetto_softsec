static void _CONSTRUCTOR lib_init(void)
{
int ret;
const char *e;

	if (_gnutls_global_init_skip() != 0)
		return;

	e = getenv("STR");
	if (e != NULL) {
		ret = atoi(e);
		if (ret == 1)
			return;
	}

	ret = gnutls_global_init();
	if (ret < 0) {
		fprintf(stderr, "STR", gnutls_strerror(ret));
		_gnutls_switch_lib_state(LIB_STATE_ERROR);
	}
}