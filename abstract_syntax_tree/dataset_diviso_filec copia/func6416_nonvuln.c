p11_kit_iter_begin (P11KitIter *iter,
                    CK_FUNCTION_LIST_PTR *modules)
{
	int i;

	return_if_fail (modules != NULL);

	finish_iterating (iter, CKR_OK);

	
	for (i = 0; modules[i] != NULL; i++) {
		if (!p11_array_push (iter->modules, modules[i]))
			return_if_reached ();
	}

	iter->iterating = 1;
	iter->searched = 1;
}