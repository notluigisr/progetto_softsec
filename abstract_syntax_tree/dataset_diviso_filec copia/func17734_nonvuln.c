bool smb2cli_tcon_is_encryption_on(struct smbXcli_tcon *tcon)
{
	return tcon->smb2.should_encrypt;
}