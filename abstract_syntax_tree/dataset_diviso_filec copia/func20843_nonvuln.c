TEST_F(RouterTest, InternalRedirectRejectedWithEmptyLocation) {
  enableRedirects();
  sendRequest();

  redirect_headers_->setLocation("");

  EXPECT_CALL(callbacks_, recreateStream(_)).Times(0);

  response_decoder_->decodeHeaders(std::move(redirect_headers_), false);

  Buffer::OwnedImpl data("STR");
  response_decoder_->decodeData(data, true);
  EXPECT_EQ(1U, cm_.thread_local_cluster_.cluster_.info_->stats_store_
                    .counter("STR")
                    .value());
  EXPECT_EQ(1UL, stats_store_.counter("STR").value());
}