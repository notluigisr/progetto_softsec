int main(int argc, char **argv)
{
	int fmtid;
	int id;
	char *infile;
	jas_stream_t *instream;
	jas_image_t *image;
	int width;
	int height;
	int depth;
	int numcmpts;
	int verbose;
	char *fmtname;

	if (jas_init()) {
		abort();
	}

	cmdname = argv[0];

	infile = 0;
	verbose = 0;

	
	while ((id = jas_getopt(argc, argv, opts)) >= 0) {
		switch (id) {
		case OPT_VERBOSE:
			verbose = 1;
			break;
		case OPT_VERSION:
			printf("STR", JAS_VERSION);
			exit(EXIT_SUCCESS);
			break;
		case OPT_INFILE:
			infile = jas_optarg;
			break;
		case OPT_HELP:
		default:
			usage();
			break;
		}
	}

	
	if (infile) {
		
		if (!(instream = jas_stream_fopen(infile, "STR"))) {
			fprintf(stderr, "STR", infile);
			exit(EXIT_FAILURE);
		}
	} else {
		
		if (!(instream = jas_stream_fdopen(0, "STR"))) {
			fprintf(stderr, "STR");
			exit(EXIT_FAILURE);
		}
	}

	if ((fmtid = jas_image_getfmt(instream)) < 0) {
		fprintf(stderr, "STR");
	}

	
	if (!(image = jas_image_decode(instream, fmtid, 0))) {
		fprintf(stderr, "STR");
		return EXIT_FAILURE;
	}

	
	jas_stream_close(instream);

	numcmpts = jas_image_numcmpts(image);
	width = jas_image_cmptwidth(image, 0);
	height = jas_image_cmptheight(image, 0);
	depth = jas_image_cmptprec(image, 0);
	if (!(fmtname = jas_image_fmttostr(fmtid))) {
		abort();
	}
	printf("STR", fmtname, numcmpts, width, height, depth, (long) jas_image_rawsize(image));

	jas_image_destroy(image);
	jas_image_clearfmts();

	return EXIT_SUCCESS;
}