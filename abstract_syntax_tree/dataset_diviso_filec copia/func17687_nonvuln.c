static int ipv6_hex(unsigned char *out, const char *in, int inlen)
	{
	unsigned char c;
	unsigned int num = 0;
	if (inlen > 4)
		return 0;
	while(inlen--)
		{
		c = *in++;
		num <<= 4;
		if ((c >= '0') && (c <= '9'))
			num |= c - '0';
		else if ((c >= 'A') && (c <= 'F'))
			num |= c - 'A' + 10;
		else if ((c >= 'a') && (c <= 'f'))
			num |=  c - 'a' + 10;
		else
			return 0;
		}
	out[0] = num >> 8;
	out[1] = num & 0xff;
	return 1;
	}