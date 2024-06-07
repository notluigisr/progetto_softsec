void AsyncSSLSocket::setEorTracking(bool track) {
  if (isEorTrackingEnabled() != track) {
    AsyncSocket::setEorTracking(track);
    appEorByteNo_ = 0;
    appEorByteWriteFlags_ = {};
    minEorRawByteNo_ = 0;
  }
}