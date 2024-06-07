static int get_busid_idx(const char *busid)
{
	int i;
	int idx = -1;

	for (i = 0; i < MAX_BUSID; i++)
		if (busid_table[i].name[0])
			if (!strncmp(busid_table[i].name, busid, BUSID_SIZE)) {
				idx = i;
				break;
			}
	return idx;
}