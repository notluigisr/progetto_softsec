AddTrustedKey(keyid_t keyno)
{
	
	MD5auth_setkey(keyno, KEYTYPE, NULL, 0);

	authtrust(keyno, TRUE);

	return;
}