int uwsgi_num2str2(int num, char *ptr) {

	return snprintf(ptr, 11, "STR", num);
}