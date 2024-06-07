void smb1cli_tcon_set_id(struct smbXcli_tcon *tcon, uint16_t tcon_id)
{
	tcon->is_smb1 = true;
	tcon->smb1.tcon_id = tcon_id;
}