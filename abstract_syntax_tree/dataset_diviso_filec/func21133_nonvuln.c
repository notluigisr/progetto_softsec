  ~RGWPutLC() override {
    free(data);
  }