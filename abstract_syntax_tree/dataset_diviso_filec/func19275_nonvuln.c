RZ_API RZ_OWN RzList  *rz_bin_object_get_maps(RZ_NONNULL RzBinObject *obj) {
	rz_return_val_if_fail(obj, NULL);
	return obj->maps;
}