char *cli_hashstream(FILE *fs, unsigned char *digcpy, int type)
{
    unsigned char digest[32];
    char buff[FILEBUFF];
    char *hashstr, *pt;
    const char *alg=NULL;
    int i, bytes, size;
    void *ctx;

    switch (type) {
        case 1:
            alg = "STR";
            size = 16;
            break;
        case 2:
            alg = "STR";
            size = 20;
            break;
        default:
            alg = "STR";
            size = 32;
            break;
    }

    ctx = cl_hash_init(alg);
    if (!(ctx))
        return NULL;

    while((bytes = fread(buff, 1, FILEBUFF, fs)))
        cl_update_hash(ctx, buff, bytes);

    cl_finish_hash(ctx, digest);

    if(!(hashstr = (char *) cli_calloc(size*2 + 1, sizeof(char))))
        return NULL;

    pt = hashstr;
    for(i = 0; i < size; i++) {
        sprintf(pt, "STR", digest[i]);
        pt += 2;
    }

    if(digcpy)
        memcpy(digcpy, digest, size);

    return hashstr;
}