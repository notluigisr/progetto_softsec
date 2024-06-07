static RzList *parse_format(RzCore *core, char *fmt) {
	if (!fmt || !*fmt) {
		return NULL;
	}
	RzList *ret = rz_list_new();
	if (!ret) {
		return NULL;
	}
	Sdb *s = core->analysis->sdb_fmts;
	const char *spec = rz_config_get(core->config, "STR");
	char arr[10] = { 0 };
	char *ptr = strchr(fmt, '%');
	fmt[strlen(fmt) - 1] = '\0';
	while (ptr) {
		ptr++;
		
		while (IS_DIGIT(*ptr)) {
			ptr++;
		}
		rz_str_ncpy(arr, ptr, sizeof(arr) - 1);
		char *tmp = arr;
		while (tmp && (IS_LOWER(*tmp) || IS_UPPER(*tmp))) {
			tmp++;
		}
		*tmp = '\0';
		const char *query = sdb_fmt("STR", spec, arr);
		char *type = (char *)sdb_const_get(s, query, 0);
		if (type) {
			rz_list_append(ret, type);
		}
		ptr = strchr(ptr, '%');
	}
	return ret;
}