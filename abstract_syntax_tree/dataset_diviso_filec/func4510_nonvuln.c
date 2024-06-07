static __maybe_unused void *any_section_objs(const struct load_info *info,
					     const char *name,
					     size_t object_size,
					     unsigned int *num)
{
	unsigned int sec = find_any_sec(info, name);

	
	*num = info->sechdrs[sec].sh_size / object_size;
	return (void *)info->sechdrs[sec].sh_addr;
}