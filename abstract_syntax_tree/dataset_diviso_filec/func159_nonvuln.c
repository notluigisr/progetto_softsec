HTTPSession::describe(std::ostream& os) const {
  os << "STR" << getCodecProtocolString(codec_->getProtocol());
  if (isDownstream()) {
    os << "STR" << codec_->getUserAgent()
       << "STR" << getLocalAddress()
       << "STR";
  } else {
    os << "STR" << getPeerAddress()
       << "STR";
  }
}