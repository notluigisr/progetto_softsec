void kwajd_open_test_01() {
    struct mskwaj_decompressor *kwajd;
    struct mskwajd_header *hdr;

    kwajd = mspack_create_kwaj_decompressor(NULL);
    TEST(kwajd != NULL);

    hdr = kwajd->open(kwajd, "STR");
    TEST(hdr != NULL);
    TEST(hdr->filename == NULL);
    kwajd->close(kwajd, hdr);


    hdr = kwajd->open(kwajd, testfile);  \
    TEST(hdr != NULL);                   \
    TEST(hdr->filename != NULL);         \
    TEST(!strcmp(fname, hdr->filename)); \
    kwajd->close(kwajd, hdr)

    hdr = kwajd->open(kwajd, testfile);  \
    TEST(hdr == NULL);                   \
    TEST(kwajd->last_error(kwajd) == MSPACK_ERR_DATAFORMAT)

    TEST_FNAME("STR");
    TEST_FNAME("STR");
    TEST_FNAME("STR");

    TEST_FNAME("STR");
    TEST_FNAME("STR");
    TEST_FNAME("STR");
    TEST_FNAME("STR");

    TEST_FNAME("STR");
    TEST_FNAME("STR");
    TEST_FNAME("STR");
    TEST_FNAME("STR");

    TEST_FNAME("STR");
    TEST_FNAME("STR");
    TEST_FNAME("STR");
    TEST_FNAME("STR");

    TEST_FNAME("STR");
    TEST_FNAME("STR");
    TEST_FNAME("STR");
    TEST_FNAME("STR");

    TEST_FNAME("STR");
    TEST_FNAME("STR");
    TEST_FNAME("STR");
    TEST_FNAME("STR");

    TEST_FNAME("STR");
    TEST_FNAME("STR");
    TEST_FNAME("STR");
    TEST_FNAME("STR");

    TEST_FNAME("STR");
    TEST_FNAME("STR");
    TEST_FNAME("STR");
    TEST_FNAME("STR");

    TEST_FNAME("STR");
    TEST_FNAME("STR");
    TEST_FNAME("STR");
    TEST_FNAME("STR");

    TEST_FNAME_BAD("STR");
    TEST_FNAME_BAD("STR");
    TEST_FNAME_BAD("STR");
    TEST_FNAME_BAD("STR");
    TEST_FNAME_BAD("STR");
    TEST_FNAME_BAD("STR");
    TEST_FNAME_BAD("STR");
    TEST_FNAME_BAD("STR");
    TEST_FNAME_BAD("STR");

    TEST_FNAME_BAD("STR");
    TEST_FNAME_BAD("STR");
    TEST_FNAME_BAD("STR");
    TEST_FNAME_BAD("STR");
    TEST_FNAME_BAD("STR");


    mspack_destroy_kwaj_decompressor(kwajd);
}