  void expectDetailsRequest(const absl::string_view details) {
    EXPECT_EQ(details, request_encoder_->getStream().responseDetails());
  }