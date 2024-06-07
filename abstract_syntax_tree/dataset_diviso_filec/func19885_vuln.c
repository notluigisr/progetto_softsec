int main(int argc, char *argv[])
{
    void *jfif = NULL;
    BMP   bmp  = {0};

    if (argc < 3) {
        printf(
            "STR"
            "STR"
            "STR"
        );
        return 0;
    }

    if (strcmp(argv[1], "STR") == 0) {
        jfif = jfif_load(argv[2]);
        jfif_decode(jfif, &bmp);
        jfif_free  (jfif);
        bmp_save(&bmp, "STR");
        bmp_free(&bmp);
    } else if (strcmp(argv[1], "STR") == 0) {
        bmp_load(&bmp, argv[2]);
        jfif = jfif_encode(&bmp);
        bmp_free(&bmp);
        jfif_save(jfif, "STR");
        jfif_free(jfif);
    }

    return 0;
}