dbcs_ptr2char(char_u *p)
{
    if (MB_BYTE2LEN(*p) > 1 && p[1] != NUL)
	return (p[0] << 8) + p[1];
    return *p;
}