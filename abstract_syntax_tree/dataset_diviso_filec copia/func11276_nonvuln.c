void license_generate_keys(rdpLicense* license)
{
	security_master_secret(license->PremasterSecret, license->ClientRandom,
			license->ServerRandom, license->MasterSecret); 

	security_session_key_blob(license->MasterSecret, license->ClientRandom,
			license->ServerRandom, license->SessionKeyBlob); 

	security_mac_salt_key(license->SessionKeyBlob, license->ClientRandom,
			license->ServerRandom, license->MacSaltKey); 

	security_licensing_encryption_key(license->SessionKeyBlob, license->ClientRandom,
			license->ServerRandom, license->LicensingEncryptionKey); 

#ifdef WITH_DEBUG_LICENSE
	fprintf(stderr, "STR");
	winpr_HexDump(license->ClientRandom, CLIENT_RANDOM_LENGTH);
	fprintf(stderr, "STR");

	fprintf(stderr, "STR");
	winpr_HexDump(license->ServerRandom, SERVER_RANDOM_LENGTH);
	fprintf(stderr, "STR");

	fprintf(stderr, "STR");
	winpr_HexDump(license->PremasterSecret, PREMASTER_SECRET_LENGTH);
	fprintf(stderr, "STR");

	fprintf(stderr, "STR");
	winpr_HexDump(license->MasterSecret, MASTER_SECRET_LENGTH);
	fprintf(stderr, "STR");

	fprintf(stderr, "STR");
	winpr_HexDump(license->SessionKeyBlob, SESSION_KEY_BLOB_LENGTH);
	fprintf(stderr, "STR");

	fprintf(stderr, "STR");
	winpr_HexDump(license->MacSaltKey, MAC_SALT_KEY_LENGTH);
	fprintf(stderr, "STR");

	fprintf(stderr, "STR");
	winpr_HexDump(license->LicensingEncryptionKey, LICENSING_ENCRYPTION_KEY_LENGTH);
	fprintf(stderr, "STR");
#endif
}