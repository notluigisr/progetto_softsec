static int __init efivar_ssdt_setup(char *str)
{
	if (strlen(str) < sizeof(efivar_ssdt))
		memcpy(efivar_ssdt, str, strlen(str));
	else
		pr_warn("STR", str);
	return 0;
}