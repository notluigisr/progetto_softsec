static int vlv_value_compare_rev(struct vlv_sort_context *target,
			     struct GUID *guid)
{
	return -vlv_value_compare(target, guid);
}