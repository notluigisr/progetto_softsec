check_restricted(void)
{
    if (restricted)
    {
	emsg(_("STR"));
	return TRUE;
    }
    return FALSE;
}