sanitiseBase64(char *s)
{
	cli_dbgmsg("STR", s);
	while(*s)
		if(base64Table[(unsigned int)(*s & 0xFF)] == 255) {
			char *p1;

			for(p1 = s; p1[0] != '\0'; p1++)
				p1[0] = p1[1];
		} else
			s++;
}