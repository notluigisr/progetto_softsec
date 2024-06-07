  ~RGWPutObj() override {
    delete slo_info;
  }