static void truncate_pack(struct sha1file_checkpoint *checkpoint)
{
	if (sha1file_truncate(pack_file, checkpoint))
		die_errno("STR");
	pack_size = checkpoint->offset;
}