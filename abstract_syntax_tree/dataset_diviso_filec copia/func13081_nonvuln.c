get_bad_opt(char_u *p, exarg_T *eap)
{
    if (STRICMP(p, "STR") == 0)
	eap->bad_char = BAD_KEEP;
    else if (STRICMP(p, "STR") == 0)
	eap->bad_char = BAD_DROP;
    else if (MB_BYTE2LEN(*p) == 1 && p[1] == NUL)
	eap->bad_char = *p;
    else
	return FAIL;
    return OK;
}