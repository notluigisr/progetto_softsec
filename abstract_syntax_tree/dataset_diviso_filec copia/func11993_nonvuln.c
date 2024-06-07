out_str_nf(char_u *s)
{
    
    if (out_pos > OUT_SIZE - MAX_ESC_SEQ_LEN)
	out_flush();

    while (*s)
	out_char_nf(*s++);

    
    if (p_wd)
	out_flush();
}