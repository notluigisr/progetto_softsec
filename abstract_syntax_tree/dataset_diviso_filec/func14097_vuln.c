  virtual void requestInit() {
    m_use_error = false;
    m_errors.reset();
    xmlParserInputBufferCreateFilenameDefault(nullptr);
  }