  CdsIntegrationTest()
      : HttpIntegrationTest(Http::CodecType::HTTP2, ipVersion(),
                            ConfigHelper::discoveredClustersBootstrap(
                                sotwOrDelta() == Grpc::SotwOrDelta::Sotw ||
                                        sotwOrDelta() == Grpc::SotwOrDelta::UnifiedSotw
                                    ? "STR"
                                    : "STR")) {
    if (sotwOrDelta() == Grpc::SotwOrDelta::UnifiedSotw ||
        sotwOrDelta() == Grpc::SotwOrDelta::UnifiedDelta) {
      config_helper_.addRuntimeOverride("STR");
    }
    use_lds_ = false;
    sotw_or_delta_ = sotwOrDelta();
  }