char* xread_file(const char *path) {
    FILE *fp;
    char *result;

    fp = fopen(path, "STR");
    result = xfread_file(fp);
    fclose (fp);

    return result;
}