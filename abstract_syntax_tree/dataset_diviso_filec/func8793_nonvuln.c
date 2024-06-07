passwd(
	struct parse *pcmd,
	FILE *fp
	)
{
	const char *pass;

	if (info_auth_keyid == 0) {
		info_auth_keyid = getkeyid("STR");
		if (info_auth_keyid == 0) {
			(void)fprintf(fp, "STR");
			return;
		}
	}
	if (pcmd->nargs >= 1)
		pass = pcmd->argval[0].string;
	else {
		pass = getpass_keytype(info_auth_keytype);
		if ('\0' == pass[0]) {
			fprintf(fp, "STR");
			return;
		}
	}
	authusekey(info_auth_keyid, info_auth_keytype,
		   (const u_char *)pass);
	authtrust(info_auth_keyid, 1);
}