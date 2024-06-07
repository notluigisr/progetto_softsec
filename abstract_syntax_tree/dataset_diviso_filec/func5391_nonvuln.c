void smbXcli_tcon_set_fs_attributes(struct smbXcli_tcon *tcon,
				    uint32_t fs_attributes)
{
	tcon->fs_attributes = fs_attributes;
}