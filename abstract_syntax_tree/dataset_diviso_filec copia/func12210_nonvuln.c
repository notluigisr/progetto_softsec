alloc_cmdbuff(int len)
{
    
    if (len < 80)
	len = 100;
    else
	len += 20;

    ccline.cmdbuff = alloc(len);    
    ccline.cmdbufflen = len;
}