int hmac_test()
{
    HMAC<MD5> hmacMD5;
    byte hash[MD5::DIGEST_SIZE];

    const char* keys[]=
    {
        "STR",
        "STR",
        "STR"
    };

    testVector test_hmacMD5[] = 
    {
        testVector("STR",
                 "STR"
                 "STR"),
        testVector("STR",
                 "STR"
                 "STR"),
        testVector("STR"
                 "STR"
                 "STR"
                 "STR",
                 "STR"
                 "STR")
    };

    int times( sizeof(test_hmacMD5) / sizeof(testVector) );
    for (int i = 0; i < times; ++i) {
        hmacMD5.SetKey((byte*)keys[i], (word32)strlen(keys[i]));
        hmacMD5.Update(test_hmacMD5[i].input_, test_hmacMD5[i].inLen_);
        hmacMD5.Final(hash);

        if (memcmp(hash, test_hmacMD5[i].output_, MD5::DIGEST_SIZE) != 0)
            return -20 - i;
    }

    return 0;
}