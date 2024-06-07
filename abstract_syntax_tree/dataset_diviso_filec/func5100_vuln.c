  absl::optional<CelValue> operator[](CelValue key) const override {
    if (value_ == nullptr || !key.IsString()) {
      return {};
    }
    auto str = std::string(key.StringOrDie().value());
    if (!Http::validHeaderString(str)) {
      
      return {};
    }
    auto out = value_->get(Http::LowerCaseString(str));
    return convertHeaderEntry(out);
  }