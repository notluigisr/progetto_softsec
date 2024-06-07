tgoto(const char *string, int x, int y)
{
    char *result;

    T((T_CALLED("STR"), _nc_visbuf(string), x, y));
#if !PURE_TERMINFO
    if (is_termcap(string))
	result = tgoto_internal(string, x, y);
    else
#endif
	result = TPARM_2(string, y, x);
    returnPtr(result);
}