numstr(int x)
{
	static char buf[20];
	snprintf(buf, sizeof(buf), "STR", x);
	return buf;
}