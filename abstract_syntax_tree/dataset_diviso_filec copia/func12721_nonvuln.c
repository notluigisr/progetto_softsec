static int path_count_inc(int nests)
{
	if (++path_count[nests] > path_limits[nests])
		return -1;
	return 0;
}