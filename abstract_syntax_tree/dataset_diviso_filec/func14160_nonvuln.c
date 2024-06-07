Signature_Encoder::Signature_Encoder(const byte* dig, word32 digSz,
                                     HashType digOID, Source& source)
{
    

    
    byte digArray[MAX_DIGEST_SZ];
    word32 digestSz = SetDigest(dig, digSz, digArray);

    
    byte algoArray[MAX_ALGO_SZ];
    word32 algoSz = SetAlgoID(digOID, algoArray);

    
    byte seqArray[MAX_SEQ_SZ];
    word32 seqSz = SetSequence(digestSz + algoSz, seqArray);

    source.grow(seqSz + algoSz + digestSz);  
    source.add(seqArray,  seqSz);
    source.add(algoArray, algoSz);
    source.add(digArray,  digestSz);
}