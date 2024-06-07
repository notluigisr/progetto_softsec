p11_index_replace_all (p11_index *index,
                       CK_ATTRIBUTE *match,
                       CK_ATTRIBUTE_TYPE key,
                       p11_array *replace)
{
	CK_OBJECT_HANDLE *handles;
	CK_RV rv;
	int i;

	return_val_if_fail (index != NULL, CKR_GENERAL_ERROR);

	handles = p11_index_find_all (index, match, -1);

	rv = index_replacev (index, handles, key,
	                     replace ? (CK_ATTRIBUTE **)replace->elem : NULL,
	                     replace ? replace->num : 0);

	if (rv == CKR_OK) {
		if (replace)
			p11_array_clear (replace);
	} else {
		for (i = 0; replace && i < replace->num; i++) {
			if (!replace->elem[i]) {
				p11_array_remove (replace, i);
				i--;
			}
		}
	}

	free (handles);
	return rv;
}