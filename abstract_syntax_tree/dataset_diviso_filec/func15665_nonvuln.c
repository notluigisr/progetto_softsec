bool AsyncSSLSocket::needsPeerVerification() const {
  if (verifyPeer_ == SSLContext::SSLVerifyPeerEnum::USE_CTX) {
    return ctx_->needsPeerVerification();
  }
  return (
      verifyPeer_ == SSLContext::SSLVerifyPeerEnum::VERIFY ||
      verifyPeer_ == SSLContext::SSLVerifyPeerEnum::VERIFY_REQ_CLIENT_CERT);
}