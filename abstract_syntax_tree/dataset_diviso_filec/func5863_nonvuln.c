u_clearline(void)
{
    if (curbuf->b_u_line_ptr.ul_line != NULL)
    {
	VIM_CLEAR(curbuf->b_u_line_ptr.ul_line);
	curbuf->b_u_line_ptr.ul_len = 0;
	curbuf->b_u_line_lnum = 0;
    }
}