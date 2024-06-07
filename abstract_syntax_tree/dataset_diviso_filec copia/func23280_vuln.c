void skip_comments(FILE * file) {
	int ch;

	while (EOF != (ch = get_char(file))) {
		
		while (ch == ' ' || ch == '\t')
			ch = get_char(file);

		if (ch == EOF)
			break;

		

		if (ch != '\n' && ch != '#')
			break;

		

		while (ch != '\n' && ch != EOF)
			ch = get_char(file);

		
	}
	if (ch != EOF)
		unget_char(ch, file);
}