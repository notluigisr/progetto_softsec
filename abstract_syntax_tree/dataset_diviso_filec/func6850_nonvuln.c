  void createVerifier() {
    ON_CALL(mock_factory_, create(_, _, _, _))
        .WillByDefault(Invoke([&](const ::google::jwt_verify::CheckAudience*,
                                  const absl::optional<std::string>& provider, bool, bool) {
          return std::move(mock_auths_[provider ? provider.value() : allowfailed]);
        }));
    verifier_ = Verifier::create(proto_config_.rules(0).requires(), proto_config_.providers(),
                                 mock_factory_);
  }