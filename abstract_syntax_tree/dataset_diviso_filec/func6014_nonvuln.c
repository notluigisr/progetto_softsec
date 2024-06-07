msg_outtrans_special(
    char_u	*strstart,
    int		from,	
    int		maxlen) 
{
    char_u	*str = strstart;
    int		retval = 0;
    char	*text;
    int		attr;
    int		len;

    attr = HL_ATTR(HLF_8);
    while (*str != NUL)
    {
	
	if ((str == strstart || str[1] == NUL) && *str == ' ')
	{
	    text = "STR";
	    ++str;
	}
	else
	    text = (char *)str2special(&str, from);
	if (text[0] != NUL && text[1] == NUL)
	    
	    text = (char *)transchar_byte((char_u)text[0]);
	len = vim_strsize((char_u *)text);
	if (maxlen > 0 && retval + len >= maxlen)
	    break;
	
	msg_puts_attr(text, len > 1
		&& (*mb_ptr2len)((char_u *)text) <= 1 ? attr : 0);
	retval += len;
    }
    return retval;
}