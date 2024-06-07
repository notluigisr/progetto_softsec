p11_index_update (p11_index *index,
                  CK_OBJECT_HANDLE handle,
                  CK_ATTRIBUTE *update)
{
	index_object *obj;
	CK_RV rv;

	return_val_if_fail (index != NULL, CKR_GENERAL_ERROR);
	return_val_if_fail (update != NULL, CKR_GENERAL_ERROR);

	obj = p11_dict_get (index->objects, &handle);
	if (obj == NULL) {
		p11_attrs_free (update);
		return CKR_OBJECT_HANDLE_INVALID;
	}

	rv = index_build (index, obj->handle, &obj->attrs, update);
	if (rv != CKR_OK) {
		p11_attrs_free (update);
		return rv;
	}

	index_hash (index, obj);
	index_notify (index, obj->handle, NULL);

	return CKR_OK;
}