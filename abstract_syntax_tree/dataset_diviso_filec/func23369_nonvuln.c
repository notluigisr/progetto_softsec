bool AsyncSSLSocket::getSelectedNextProtocolNoThrow(
    const unsigned char** protoName,
    unsigned* protoLen) const {
  *protoName = nullptr;
  *protoLen = 0;
#if FOLLY_OPENSSL_HAS_ALPN
  SSL_get0_alpn_selected(ssl_.get(), protoName, protoLen);
  return true;
#else
  return false;
#endif
}