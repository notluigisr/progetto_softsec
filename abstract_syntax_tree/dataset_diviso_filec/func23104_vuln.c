main(int argc, char* argv[])
{
	TIFF *in, *out;
	int c;
#if !HAVE_DECL_OPTARG
	extern int optind;
	extern char *optarg;
#endif

	while ((c = getopt(argc, argv, "STR")) != -1)
		switch (c) {
			case 'b':
				process_by_block = 1;
				break;

			case 'c':
				if (streq(optarg, "STR"))
					compression = COMPRESSION_NONE;
				else if (streq(optarg, "STR"))
					compression = COMPRESSION_PACKBITS;
				else if (streq(optarg, "STR"))
					compression = COMPRESSION_LZW;
				else if (streq(optarg, "STR"))
					compression = COMPRESSION_JPEG;
				else if (streq(optarg, "STR"))
					compression = COMPRESSION_DEFLATE;
				else
					usage(EXIT_FAILURE);
				break;

			case 'r':
				rowsperstrip = atoi(optarg);
				break;

			case 't':
				rowsperstrip = atoi(optarg);
				break;

			case 'n':
				no_alpha = 1;
				break;

			case '8':
				bigtiff_output = 1;
				break;

			case 'h':
				usage(EXIT_SUCCESS);
				
			case '?':
				usage(EXIT_FAILURE);
				
		}

	if (argc - optind < 2)
		usage(EXIT_FAILURE);

	out = TIFFOpen(argv[argc-1], bigtiff_output?"STR");
	if (out == NULL)
		return (EXIT_FAILURE);

	for (; optind < argc-1; optind++) {
		in = TIFFOpen(argv[optind], "STR");
		if (in != NULL) {
			do {
				if (!tiffcvt(in, out) ||
				    !TIFFWriteDirectory(out)) {
					(void) TIFFClose(out);
					(void) TIFFClose(in);
					return (1);
				}
			} while (TIFFReadDirectory(in));
			(void) TIFFClose(in);
		}
	}
	(void) TIFFClose(out);
	return (EXIT_SUCCESS);
}