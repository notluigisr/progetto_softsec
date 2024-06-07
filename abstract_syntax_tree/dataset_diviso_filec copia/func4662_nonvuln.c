__zzip_aligned4(char *p)
{

    p += ((long) p) & 1;        
    p += ((long) p) & 2;        
    return p;
}