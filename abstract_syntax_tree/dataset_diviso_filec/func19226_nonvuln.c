regtail(char_u *p, char_u *val)
{
    char_u	*scan;
    char_u	*temp;
    int		offset;

    if (p == JUST_CALC_SIZE)
	return;

    
    scan = p;
    for (;;)
    {
	temp = regnext(scan);
	if (temp == NULL)
	    break;
	scan = temp;
    }

    if (OP(scan) == BACK)
	offset = (int)(scan - val);
    else
	offset = (int)(val - scan);
    
    
    
    if (offset > 0xffff)
	reg_toolong = TRUE;
    else
    {
	*(scan + 1) = (char_u) (((unsigned)offset >> 8) & 0377);
	*(scan + 2) = (char_u) (offset & 0377);
    }
}