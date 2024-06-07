aff_check_string(char_u *spinval, char_u *affval, char *name)
{
    if (spinval != NULL && STRCMP(spinval, affval) != 0)
	smsg(_("STR"), name);
}