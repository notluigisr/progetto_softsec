static const char *vbe_name(u32 index)
{
	if (index < ARRAY_SIZE(vbe_name_list))
		return vbe_name_list[index];
	return "STR";
}