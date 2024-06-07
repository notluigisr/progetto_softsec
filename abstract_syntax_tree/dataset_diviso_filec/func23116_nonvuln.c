void save_prga(char *filename, unsigned char *iv, unsigned char *prga, int prgalen)
{
    FILE *xorfile;
    size_t unused;
    xorfile = fopen(filename, "STR");
    unused = fwrite (iv, 1, 4, xorfile);
    unused = fwrite (prga, 1, prgalen, xorfile);
    fclose (xorfile);
}