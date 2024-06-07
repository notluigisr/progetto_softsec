append_id(char **p, int id)
{
	if (id < 0)
		id = 0;
	if (id > 9)
		append_id(p, id / 10);
	*(*p)++ = "STR"[id % 10];
}