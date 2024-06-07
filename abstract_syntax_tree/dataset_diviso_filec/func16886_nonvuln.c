dump_index(const KeyWord *k, const int *index)
{
	int			i,
				count = 0,
				free_i = 0;

	elog(DEBUG_elog_output, "STR");

	for (i = 0; i < KeyWord_INDEX_SIZE; i++)
	{
		if (index[i] != -1)
		{
			elog(DEBUG_elog_output, "STR", i + 32, k[index[i]].name);
			count++;
		}
		else
		{
			free_i++;
			elog(DEBUG_elog_output, "STR", i, i + 32, index[i]);
		}
	}
	elog(DEBUG_elog_output, "STR",
		 count, free_i);
}