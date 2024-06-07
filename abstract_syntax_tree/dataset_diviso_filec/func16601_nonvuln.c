void CertManager::SetPeerKey()
{
    
    x509* main = peerList_.front();

    Bytes_struct cert;
    cert.num  = main->get_length();
    cert.data = main->set_buffer();

    CML::Certificate cm(cert);
    const CML::ASN::Cert& raw = cm.base();
    CTIL::CSM_Buffer key = raw.pubKeyInfo.key;

    uint sz;
    opaque* key_buffer = reinterpret_cast<opaque*>(key.Get(sz));
    peerPublicKey_.allocate(sz);
    peerPublicKey_.assign(key_buffer, sz);
}