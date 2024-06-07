p11_index_find_all (p11_index *index,
                    CK_ATTRIBUTE *match,
                    int count)
{
	index_bucket handles = { NULL, 0 };

	return_val_if_fail (index != NULL, NULL);

	if (count < 0)
		count = p11_attrs_count (match);

	index_select (index, match, count, sink_if_match, &handles);

	
	bucket_push (&handles, 0UL);
	return handles.elem;
}