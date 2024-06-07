int rabbit_test()
{
    byte cipher[16];
    byte plain[16];

    const char* keys[] = 
    {           
        "STR",
        "STR",
        "STR"
    };

    const char* ivs[] =
    {
        "STR",
        "STR",
        0
    };


    testVector test_rabbit[] =
    {
        testVector("STR",
                   "STR"),
        testVector("STR",
                   "STR"),
        testVector("STR",
                   "STR")
    };


    int times( sizeof(test_rabbit) / sizeof(testVector) );
    for (int i = 0; i < times; ++i) {
        Rabbit::Encryption enc;
        Rabbit::Decryption dec;

        enc.SetKey((byte*)keys[i], (byte*)ivs[i]);
        dec.SetKey((byte*)keys[i], (byte*)ivs[i]);

        enc.Process(cipher, test_rabbit[i].input_, test_rabbit[i].outLen_);
        dec.Process(plain,  cipher, test_rabbit[i].outLen_);

        if (memcmp(plain, test_rabbit[i].input_, test_rabbit[i].outLen_))
            return -230 - i;

        if (memcmp(cipher, test_rabbit[i].output_, test_rabbit[i].outLen_))
            return -240 - i;
    }

    return 0;
}