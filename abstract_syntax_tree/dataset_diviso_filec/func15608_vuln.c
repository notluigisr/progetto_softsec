folly::Optional<Param> ReadRecordLayer::readEvent(
    folly::IOBufQueue& socketBuf) {
  if (!unparsedHandshakeData_.empty()) {
    auto param = decodeHandshakeMessage(unparsedHandshakeData_);
    if (param) {
      VLOG(8) << "STR"
              << toString(boost::apply_visitor(EventVisitor(), *param));
      return param;
    }
  }

  while (true) {
    
    
    auto message = read(socketBuf);
    if (!message) {
      return folly::none;
    }

    if (!unparsedHandshakeData_.empty() &&
        message->type != ContentType::handshake) {
      throw std::runtime_error("STR");
    }

    switch (message->type) {
      case ContentType::alert: {
        auto alert = decode<Alert>(std::move(message->fragment));
        if (alert.description == AlertDescription::close_notify) {
          return Param(CloseNotify(socketBuf.move()));
        } else {
          return Param(std::move(alert));
        }
      }
      case ContentType::handshake: {
        unparsedHandshakeData_.append(std::move(message->fragment));
        auto param = decodeHandshakeMessage(unparsedHandshakeData_);
        if (param) {
          VLOG(8) << "STR"
                  << toString(boost::apply_visitor(EventVisitor(), *param));
          return param;
        } else {
          
          
          
          continue;
        }
      }
      case ContentType::application_data:
        return Param(AppData(std::move(message->fragment)));
      default:
        throw std::runtime_error("STR");
    }
  }
}