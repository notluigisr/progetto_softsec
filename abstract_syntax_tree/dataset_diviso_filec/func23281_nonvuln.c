SSL::SSL(SSL_CTX* ctx) 
    : secure_(ctx->getMethod()->getVersion(), crypto_.use_random(),
              ctx->getMethod()->getSide(), ctx->GetCiphers(), ctx,
              ctx->GetDH_Parms().set_), quietShutdown_(false), has_data_(false)
{
    if (int err = crypto_.get_random().GetError()) {
        SetError(YasslError(err));
        return;
    }

    CertManager& cm = crypto_.use_certManager();
    cm.CopySelfCert(ctx->getCert());

    bool serverSide = secure_.use_parms().entity_ == server_end;

    if (ctx->getKey()) {
        if (int err = cm.SetPrivateKey(*ctx->getKey())) {
            SetError(YasslError(err));
            return;
        }
        else if (serverSide && ctx->GetCiphers().setSuites_ == 0) {
            
            
            ProtocolVersion pv = secure_.get_connection().version_;
            
            bool removeDH  = secure_.use_parms().removeDH_;
            bool removeRSA = false;
            bool removeDSA = false;
            
            if (cm.get_keyType() == rsa_sa_algo)
                removeDSA = true;
            else
                removeRSA = true;
            secure_.use_parms().SetSuites(pv, removeDH, removeRSA, removeDSA);
        }
    }
    else if (serverSide) {
        SetError(no_key_file);
        return;
    }

    if (ctx->getMethod()->verifyPeer())
        cm.setVerifyPeer();
    if (ctx->getMethod()->verifyNone())
        cm.setVerifyNone();
    if (ctx->getMethod()->failNoCert())
        cm.setFailNoCert();
    cm.setVerifyCallback(ctx->getVerifyCallback());

    if (serverSide)
        crypto_.SetDH(ctx->GetDH_Parms());

    const SSL_CTX::CertList& ca = ctx->GetCA_List();
    SSL_CTX::CertList::const_iterator first(ca.begin());
    SSL_CTX::CertList::const_iterator last(ca.end());

    while (first != last) {
        if (int err = cm.CopyCaCert(*first)) {
            SetError(YasslError(err));
            return;
        }
        ++first;
    }
}