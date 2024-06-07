static void check_file(char *basename)
{
    gdImagePtr im;
    char *buffer;
    size_t size;

    size = read_test_file(&buffer, basename);
    im = gdImageCreateFromTgaPtr(size, (void *) buffer);
    gdTestAssert(im == NULL);
    free(buffer);
}