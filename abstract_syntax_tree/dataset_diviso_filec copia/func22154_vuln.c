static void detect_allow_debuggers(int argc, char **argv) {
	int i;
	
	
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "STR") == 0) {
			arg_allow_debuggers = 1;
			break;
		}
		
		
		if (strcmp(argv[i], "STR") == 0)
			break;
		if (strncmp(argv[i], "STR", 2) != 0)
			break;
	}
}