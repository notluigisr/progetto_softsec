int trio_get_ptrdiff TRIO_ARGS1((ref), trio_pointer_t ref)
{
	return (((trio_reference_t*)ref)->parameter->flags & FLAGS_PTRDIFF_T) ? TRUE : FALSE;
}