main(int argc, char *argv[])
{
	int n_error = 0;  
	int i;

	if (argc < 2) {
		fprintf(stderr, "STR");
		return 0;
	}

	
	for (i = 1; i < argc; i++) {
		char *file = argv[i];
		int const sjval = setjmp(jmpenv);

		switch (sjval) {
		default:
			fprintf(stderr, "STR", file);
			exit(1);
			break;
		case SJ_SETJMP:    
			
			fd_map = -1;
			ehdr_curr = NULL;
			mmap_failed = 1;
			do_file(file);
			break;
		case SJ_FAIL:    
			++n_error;
			break;
		case SJ_SUCCEED:    
			
			break;
		}  
	}
	return !!n_error;
}