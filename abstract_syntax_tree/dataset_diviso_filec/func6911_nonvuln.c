zfs_ace_fuid_get_who(void *args)
{
	uint16_t entry_type;
	zfs_ace_t *acep = args;

	entry_type = acep->z_hdr.z_flags & ACE_TYPE_FLAGS;

	if (entry_type == ACE_OWNER || entry_type == OWNING_GROUP ||
	    entry_type == ACE_EVERYONE)
		return (-1);
	return (((zfs_ace_t *)acep)->z_fuid);
}