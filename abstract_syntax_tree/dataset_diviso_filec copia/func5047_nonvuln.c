get_viminfo_parameter(int type)
{
    char_u  *p;

    p = find_viminfo_parameter(type);
    if (p != NULL && VIM_ISDIGIT(*p))
	return atoi((char *)p);
    return -1;
}