void ClientDiffieHellmanPublic::build(SSL& ssl)
{
    DiffieHellman& dhServer = ssl.useCrypto().use_dh();
    DiffieHellman  dhClient(dhServer);

    uint keyLength = dhClient.get_agreedKeyLength(); 

    alloc(keyLength, true);
    dhClient.makeAgreement(dhServer.get_publicKey(), keyLength);
    c16toa(keyLength, Yc_);
    memcpy(Yc_ + KEY_OFFSET, dhClient.get_publicKey(), keyLength);

    
    if (*dhClient.get_agreedKey() == 0) 
        ssl.set_preMaster(dhClient.get_agreedKey() + 1, keyLength - 1);
    else
        ssl.set_preMaster(dhClient.get_agreedKey(), keyLength);
}