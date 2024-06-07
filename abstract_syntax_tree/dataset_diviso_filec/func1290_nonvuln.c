static int replmd_replPropertyMetaData1_attid_sort(const struct replPropertyMetaData1 *m1,
						   const struct replPropertyMetaData1 *m2)
{
	
	uint32_t attid_1 = m1->attid;
	uint32_t attid_2 = m2->attid;

	if (attid_1 == attid_2) {
		return 0;
	}

	
	return attid_1 > attid_2 ? 1 : -1;
}