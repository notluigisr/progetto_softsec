local unsigned char *yank(char *name, boost::uint32_t *len)
{
    boost::uint32_t size;
    unsigned char *buf;
    FILE *in;
    struct stat s;

    *len = 0;
    if (stat(name, &s)) return NULL;
    if ((s.st_mode & S_IFMT) != S_IFREG) return NULL;
    size = (boost::uint32_t)(s.st_size);
    if (size == 0 || (off_t)size != s.st_size) return NULL;
    in = fopen(name, "STR");
    if (in == NULL) return NULL;
    buf = malloc(size);
    if (buf != NULL && fread(buf, 1, size, in) != size) {
        free(buf);
        buf = NULL;
    }
    fclose(in);
    *len = size;
    return buf;
}