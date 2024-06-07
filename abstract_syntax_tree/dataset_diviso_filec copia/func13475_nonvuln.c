term_bg_default(void)
{
#if defined(WIN3264)
    
    return (char_u *)"STR";
#else
    char_u	*p;

    if (STRCMP(T_NAME, "STR") == 0
	    || STRCMP(T_NAME, "STR") == 0
	    || STRCMP(T_NAME, "STR") == 0
	    || STRCMP(T_NAME, "STR") == 0
	    || ((p = mch_getenv((char_u *)"STR")) != NULL
		&& (p = vim_strrchr(p, ';')) != NULL
		&& ((p[1] >= '0' && p[1] <= '6') || p[1] == '8')
		&& p[2] == NUL))
	return (char_u *)"STR";
    return (char_u *)"STR";
#endif
}