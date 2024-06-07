  void reset()
  {
    bzero(this, sizeof(*this));
    ssl_type= SSL_TYPE_NOT_SPECIFIED;
  }