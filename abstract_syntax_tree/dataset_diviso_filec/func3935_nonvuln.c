void CertificateVerify::Process(input_buffer& input, SSL& ssl)
{
    if (input.get_error()) {
        ssl.SetError(bad_input);
        return;
    }

    const Hashes&      hashVerify = ssl.getHashes().get_certVerify();
    const CertManager& cert       = ssl.getCrypto().get_certManager();

    if (cert.get_peerKeyType() == rsa_sa_algo) {
        RSA rsa(cert.get_peerKey(), cert.get_peerKeyLength());

        if (!rsa.verify(hashVerify.md5_, sizeof(hashVerify), signature_,
                        get_length()))
            ssl.SetError(verify_error);
    }
    else { 
        byte decodedSig[DSS_SIG_SZ];
        TaoCrypt::DecodeDSA_Signature(decodedSig, signature_, get_length());
        
        DSS dss(cert.get_peerKey(), cert.get_peerKeyLength());
        if (!dss.verify(hashVerify.sha_, SHA_LEN, decodedSig, get_length()))
            ssl.SetError(verify_error);
    }
}