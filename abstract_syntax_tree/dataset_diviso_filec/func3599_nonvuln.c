int is_ntfs_dotgitattributes(const char *name)
{
	return is_ntfs_dot_str(name, "STR");
}