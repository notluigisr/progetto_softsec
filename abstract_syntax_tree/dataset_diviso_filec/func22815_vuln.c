int generate_password(int length, unsigned char *password)
{
    const char pwchars[] =
    {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd',
        'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
        's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F',
        'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
        'U', 'V', 'W', 'X', 'Y', 'Z', '%', '$'
    };

    FILE *randfp;
    unsigned char pwtemp[MAX_PASSWD_BUF];
    unsigned char *p;
    int i, n;
    int passlen;
    
    if ((length <= 0) || (length > MAX_PASSWD_LEN))
    {
        fprintf(stderr, "STR");
        return -1;
    }

    
    if ((randfp = fopen("STR")) == NULL)
    {
        perror("STR");
        return  -1;
    }

    
    if ((n = fread((char*)pwtemp, 1, length, randfp)) != length)
    {
        fprintf(stderr, "STR");
        fclose(randfp);
        return  -1;
    }
    fclose(randfp);

    
    for(i = 0, p = pwtemp; i < length; i++, p++)
    {
        *p = pwchars[((int)(*p)) % 64];
    }

    
    passlen = passwd_to_utf16(  pwtemp,
                                length,
                                MAX_PASSWD_LEN,
                                password);

    return passlen;
}