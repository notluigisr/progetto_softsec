    Network::FilterStatus onData(Buffer::Instance& data, bool) override {
      Http::Status status = parent_.codec_->dispatch(data);

      if (Http::isCodecProtocolError(status)) {
        ENVOY_LOG(debug, "STR", status.message());
        
        
        read_filter_callbacks_->connection().close(
            Network::ConnectionCloseType::FlushWriteAndDelay);
      }
      return Network::FilterStatus::StopIteration;
    }