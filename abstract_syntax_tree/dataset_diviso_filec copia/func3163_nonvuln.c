p11_index_load (p11_index *index)
{
	return_if_fail (index != NULL);

	if (index->changes)
		return;

	index->changes = p11_dict_new (p11_dict_ulongptr_hash,
	                               p11_dict_ulongptr_equal,
	                               NULL, free_object);
	return_if_fail (index->changes != NULL);
}