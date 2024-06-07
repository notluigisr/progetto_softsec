  void addStreamDecoderFilter(StreamDecoderFilterSharedPtr filter,
                              Matcher::MatchTreeSharedPtr<HttpMatchingData> match_tree) override {
    if (match_tree) {
      addStreamDecoderFilterWorker(
          filter,
          std::make_shared<FilterMatchState>(std::move(match_tree),
                                             std::make_shared<Matching::HttpMatchingDataImpl>()),
          false);
      return;
    }

    addStreamDecoderFilterWorker(filter, nullptr, false);
  }