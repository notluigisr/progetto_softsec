  ~RGWPutACLs() override {
    free(data);
  }