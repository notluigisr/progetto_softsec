write_viminfo_sub_string(FILE *fp)
{
    char_u *old_sub = get_old_sub();

    if (get_viminfo_parameter('/') != 0 && old_sub != NULL)
    {
	fputs(_("STR"), fp);
	viminfo_writestring(fp, old_sub);
    }
}