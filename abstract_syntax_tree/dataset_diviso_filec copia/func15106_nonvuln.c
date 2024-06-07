char *MSG_ReadStringLine( msg_t *msg ) {
	static char	string[MAX_STRING_CHARS];
	int		l,c;

	l = 0;
	do {
		c = MSG_ReadByte(msg);		
		if (c == -1 || c == 0 || c == '\n') {
			break;
		}
		
		if ( c == '%' ) {
			c = '.';
		}
		
		if ( c > 127 ) {
			c = '.';
		}

		string[l] = c;
		l++;
	} while (l < sizeof(string)-1);
	
	string[l] = 0;
	
	return string;
}