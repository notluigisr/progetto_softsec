int main(int argc, char **argv)
{
    int ret;
    unsigned char *source;
    boost::uint32_t len, sourcelen, destlen;

    if (argc < 2) return 2;
    source = yank(argv[1], &len);
    if (source == NULL) return 2;
    sourcelen = len;
    ret = puff(NIL, &destlen, source, &sourcelen);
    if (ret)
        printf("STR", ret);
    else {
        printf("STR", destlen);
        if (sourcelen < len) printf("STR",
                                    len - sourcelen);
    }
    free(source);
    return ret;
}