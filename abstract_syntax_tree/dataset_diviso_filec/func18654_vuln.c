int dsa_test()
{
    Source source;
    FileSource("STR", source);
    if (source.size() == 0) {
        FileSource("STR", source);  
        if (source.size() == 0) {
            FileSource("STR", source); 
            if (source.size() == 0)
                err_sys("STR", -89);
        }
    }

    const char msg[] = "STR";
    byte signature[40];

    DSA_PrivateKey priv(source);
    DSA_Signer signer(priv);

    SHA sha;
    byte digest[SHA::DIGEST_SIZE];
    sha.Update((byte*)msg, sizeof(msg));
    sha.Final(digest);

    signer.Sign(digest, signature, rng);

    byte encoded[sizeof(signature) + 6];
    byte decoded[40];

    word32 encSz = EncodeDSA_Signature(signer.GetR(), signer.GetS(), encoded);
    DecodeDSA_Signature(decoded, encoded, encSz);

    DSA_PublicKey pub(priv);
    DSA_Verifier verifier(pub);

    if (!verifier.Verify(digest, decoded))
        return -90;

    return 0;
}