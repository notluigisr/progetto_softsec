archive_write_disk_set_acls(struct archive *a, int fd, const char *name,
    struct archive_acl *abstract_acl, __LA_MODE_T mode)
{
	int		ret = ARCHIVE_OK;

#if !ARCHIVE_ACL_LIBRICHACL
	(void)mode;	
#endif

#if ARCHIVE_ACL_LIBRICHACL
	if ((archive_acl_types(abstract_acl)
	    & ARCHIVE_ENTRY_ACL_TYPE_NFS4) != 0) {
		ret = set_richacl(a, fd, name, abstract_acl, mode,
		    ARCHIVE_ENTRY_ACL_TYPE_NFS4, "STR");
	}
#if ARCHIVE_ACL_LIBACL
	else
#endif
#endif	
#if ARCHIVE_ACL_LIBACL
	if ((archive_acl_types(abstract_acl)
	    & ARCHIVE_ENTRY_ACL_TYPE_POSIX1E) != 0) {
		if ((archive_acl_types(abstract_acl)
		    & ARCHIVE_ENTRY_ACL_TYPE_ACCESS) != 0) {
			ret = set_acl(a, fd, name, abstract_acl,
			    ARCHIVE_ENTRY_ACL_TYPE_ACCESS, "STR");
			if (ret != ARCHIVE_OK)
				return (ret);
		}
		if ((archive_acl_types(abstract_acl)
		    & ARCHIVE_ENTRY_ACL_TYPE_DEFAULT) != 0)
			ret = set_acl(a, fd, name, abstract_acl,
			    ARCHIVE_ENTRY_ACL_TYPE_DEFAULT, "STR");
	}
#endif	
	return (ret);
}