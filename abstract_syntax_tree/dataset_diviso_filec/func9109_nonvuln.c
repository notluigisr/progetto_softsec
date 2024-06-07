int CertManager::SetPrivateKey(const x509& key)
{
    privateKey_.allocate(key.get_length());
    privateKey_.assign(key.get_buffer(), key.get_length());

    
    if (x509* cert = list_.front()) {
        TaoCrypt::Source source(cert->get_buffer(), cert->get_length());
        TaoCrypt::CertDecoder cd(source, false);
        cd.DecodeToKey();
        if (int err = cd.GetError().What())
            return err;
        if (cd.GetKeyType() == TaoCrypt::RSAk)
            keyType_ = rsa_sa_algo;
        else
            keyType_ = dsa_sa_algo;
    }
    return 0;
}