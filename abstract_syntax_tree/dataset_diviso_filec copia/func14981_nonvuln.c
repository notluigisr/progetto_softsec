int dm_persistent_snapshot_init(void)
{
	int r;

	r = dm_exception_store_type_register(&_persistent_type);
	if (r) {
		DMERR("STR");
		return r;
	}

	r = dm_exception_store_type_register(&_persistent_compat_type);
	if (r) {
		DMERR("STR"
		      "STR");
		dm_exception_store_type_unregister(&_persistent_type);
		return r;
	}

	return r;
}