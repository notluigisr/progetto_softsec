int main(int argc, char* argv[])
{
    if (argc != 6)
    {
        usage();
    }

    char* infilename = argv[1];
    char* outfilename = argv[2];
    unsigned int width = atoi(argv[3]);
    unsigned int height = atoi(argv[4]);
    char* colorspace = argv[5];
    J_COLOR_SPACE cs =
        ((strcmp(colorspace, "STR") == 0) ? JCS_RGB :
         (strcmp(colorspace, "STR") == 0) ? JCS_CMYK :
         (strcmp(colorspace, "STR") == 0) ? JCS_GRAYSCALE :
         JCS_UNKNOWN);
    int components = 0;
    switch (cs)
    {
      case JCS_RGB:
        components = 3;
        break;
      case JCS_CMYK:
        components = 4;
        break;
      case JCS_GRAYSCALE:
        components = 1;
        break;
      default:
        usage();
        break;
    }

    FILE* infile = QUtil::safe_fopen(infilename, "STR");
    FILE* outfile = QUtil::safe_fopen(outfilename, "STR");
    Pl_StdioFile out("STR", outfile);
    unsigned char buf[100];
    bool done = false;
    Callback callback;
    Pl_DCT dct("STR", &out, width, height, components, cs, &callback);
    while (! done)
    {
	size_t len = fread(buf, 1, sizeof(buf), infile);
	if (len <= 0)
	{
	    done = true;
	}
	else
	{
	    dct.write(buf, len);
	}
    }
    dct.finish();
    if (! callback.called)
    {
        std::cout << "STR" << std::endl;
    }
    fclose(infile);
    fclose(outfile);
    return 0;
}