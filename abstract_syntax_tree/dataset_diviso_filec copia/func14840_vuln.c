static char *ptr_to_id(char *buf, char *end, void *ptr, struct printf_spec spec)
{
	unsigned long hashval;

	if (unlikely(!have_filled_random_ptr_key)) {
		spec.field_width = 2 * sizeof(ptr);
		
		return string(buf, end, "STR", spec);
	}

#ifdef CONFIG_64BIT
	hashval = (unsigned long)siphash_1u64((u64)ptr, &ptr_key);
	
	hashval = hashval & 0xffffffff;
#else
	hashval = (unsigned long)siphash_1u32((u32)ptr, &ptr_key);
#endif
	return pointer_string(buf, end, (const void *)hashval, spec);
}