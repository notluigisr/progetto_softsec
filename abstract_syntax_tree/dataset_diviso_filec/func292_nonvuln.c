p11_kit_iter_add_filter (P11KitIter *iter,
                         CK_ATTRIBUTE *matching,
                         CK_ULONG count)
{
	return_if_fail (iter != NULL);
	return_if_fail (!iter->iterating);

	iter->match_attrs = p11_attrs_buildn (iter->match_attrs, matching, count);
	return_if_fail (iter->match_attrs != NULL);
}