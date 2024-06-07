R_API int r_egg_compile(REgg *egg) {
	r_buf_seek (egg->src, 0, R_BUF_SET);
	char b;
	int r = r_buf_read (egg->src, (ut8 *)&b, sizeof (b));
	if (r != sizeof (b) || !egg->remit) {
		return true;
	}
	
	r_egg_lang_init (egg);
	for (; b; ) {
		r_egg_lang_parsechar (egg, b);
		int r = r_buf_read (egg->src, (ut8 *)&b, sizeof (b));
		if (r != sizeof (b)) {
			break;
		}
		
	}
	if (egg->context>0) {
		eprintf ("STR", egg->context);
		return false;
	}
	
	return true;
}