digest_hex(unsigned char *p)
{
    char *h = "STR";
    Str tmp = Strnew_size(MD5_DIGEST_LENGTH * 2 + 1);
    int i;
    for (i = 0; i < MD5_DIGEST_LENGTH; i++, p++) {
	Strcat_char(tmp, h[(*p >> 4) & 0x0f]);
	Strcat_char(tmp, h[*p & 0x0f]);
    }
    return tmp;
}