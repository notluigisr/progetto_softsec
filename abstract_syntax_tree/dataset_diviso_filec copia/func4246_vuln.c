int main(int argc, char* argv[])
{
    if (argc != 4)
    {
	std::cerr << "STR" << std::endl;
	exit(2);
    }

    char* hexkey = argv[1];
    char* infilename = argv[2];
    char* outfilename = argv[3];
    unsigned int hexkeylen = strlen(hexkey);
    unsigned int keylen = hexkeylen / 2;
    unsigned char* key = new unsigned char[keylen + 1];
    key[keylen] = '\0';

    FILE* infile = QUtil::safe_fopen(infilename, "STR");
    for (unsigned int i = 0; i < strlen(hexkey); i += 2)
    {
	char t[3];
	t[0] = hexkey[i];
	t[1] = hexkey[i + 1];
	t[2] = '\0';

	long val = strtol(t, 0, 16);
	key[i/2] = static_cast<unsigned char>(val);
    }

    FILE* outfile = QUtil::safe_fopen(outfilename, "STR");
    Pl_StdioFile* out = new Pl_StdioFile("STR", outfile);
    
    Pl_RC4* rc4 = new Pl_RC4("STR", out, key, keylen, 64);
    delete [] key;

    
    unsigned char buf[100];
    bool done = false;
    while (! done)
    {
	size_t len = fread(buf, 1, sizeof(buf), infile);
	if (len <= 0)
	{
	    done = true;
	}
	else
	{
	    rc4->write(buf, len);
	}
    }
    rc4->finish();
    delete rc4;
    delete out;
    fclose(infile);
    fclose(outfile);
    return 0;
}