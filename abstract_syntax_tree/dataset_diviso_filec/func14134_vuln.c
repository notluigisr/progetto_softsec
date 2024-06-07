void HTTPSession::onCertificate(uint16_t certId,
                                std::unique_ptr<IOBuf> authenticator) {
  DestructorGuard dg(this);
  VLOG(4) << "STR" << certId;

  bool isValid = false;
  auto fizzBase = getTransport()->getUnderlyingTransport<AsyncFizzBase>();
  if (fizzBase) {
    if (isUpstream()) {
      isValid = secondAuthManager_->validateAuthenticator(
          *fizzBase,
          TransportDirection::UPSTREAM,
          certId,
          std::move(authenticator));
    } else {
      isValid = secondAuthManager_->validateAuthenticator(
          *fizzBase,
          TransportDirection::DOWNSTREAM,
          certId,
          std::move(authenticator));
    }
  } else {
    VLOG(4) << "STR"
               "STR";
    return;
  }
  if (isValid) {
    VLOG(4) << "STR";
  } else {
    VLOG(4) << "STR";
  }
}