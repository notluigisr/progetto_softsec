  void accept_connection(int fd) {
    util::make_socket_nodelay(fd);
    SSL *ssl = nullptr;
    if (ssl_ctx_) {
      ssl = ssl_session_new(fd);
      if (!ssl) {
        close(fd);
        return;
      }
    }
    auto handler =
        std::make_unique<Http2Handler>(this, fd, ssl, get_next_session_id());
    if (!ssl) {
      if (handler->connection_made() != 0) {
        return;
      }
    }
    add_handler(handler.release());
  }