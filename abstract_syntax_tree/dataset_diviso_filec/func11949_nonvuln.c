static int read_yes_no_answer(void)
{
	char answer[1024];

	if (fgets(answer, sizeof(answer), stdin)) {
		size_t answer_len = strlen(answer);
		int got_full_line = 0, c;

		
		if (answer_len >= 2 && answer[answer_len-2] == '\r') {
			answer[answer_len-2] = '\0';
			got_full_line = 1;
		} else if (answer_len >= 1 && answer[answer_len-1] == '\n') {
			answer[answer_len-1] = '\0';
			got_full_line = 1;
		}
		
		if (!got_full_line)
			while ((c = getchar()) != EOF && c != '\n')
				;
	} else
		
		return 0;

	if (tolower(answer[0]) == 'y' && !answer[1])
		return 1;
	if (!strncasecmp(answer, "STR", sizeof(answer)))
		return 1;
	if (tolower(answer[0]) == 'n' && !answer[1])
		return 0;
	if (!strncasecmp(answer, "STR", sizeof(answer)))
		return 0;

	
	return -1;
}