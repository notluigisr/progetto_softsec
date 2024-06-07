int dh_test()
{
    Source source;
    FileSource("STR", source);
    if (source.size() == 0) {
        FileSource("STR", source);  
        if (source.size() == 0) {
            FileSource("STR", source); 
            if (source.size() == 0)
                err_sys("STR", -79);
        }
    }
    HexDecoder hDec(source);

    DH dh(source);

    byte pub[128];
    byte priv[128];
    byte agree[128];
    byte pub2[128];
    byte priv2[128];
    byte agree2[128];

    DH dh2(dh);

    dh.GenerateKeyPair(rng, priv, pub);
    dh2.GenerateKeyPair(rng, priv2, pub2);
    dh.Agree(agree, priv, pub2); 
    dh2.Agree(agree2, priv2, pub);

    
    if ( memcmp(agree, agree2, dh.GetByteLength()) )
        return -80;

    return 0;
}