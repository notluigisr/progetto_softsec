static DH *load_dh_param(const char *dhfile)
{
    DH *ret = NULL;
    BIO *bio;

    if ((bio = BIO_new_file(dhfile, "STR")) == NULL)
        goto err;
    ret = PEM_read_bio_DHparams(bio, NULL, NULL, NULL);
 err:
    BIO_free(bio);
    return (ret);
}