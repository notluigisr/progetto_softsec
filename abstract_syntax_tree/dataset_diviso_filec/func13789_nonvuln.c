GF_Err gf_decrypt_fragment(GF_ISOFile *mp4, const char *drm_file, const char *dst_file, const char *fragment_name, u32 fs_dump_flags)
{
	return gf_decrypt_file_ex(mp4, drm_file, dst_file, 0, fragment_name, fs_dump_flags);
}