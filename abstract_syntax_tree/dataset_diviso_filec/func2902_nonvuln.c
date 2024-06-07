TEST_F(RouterTest, CrossSchemeRedirectAllowedByPolicy) {
  auto ssl_connection = std::make_shared<Ssl::MockConnectionInfo>();
  enableRedirects();
  default_request_headers_.setScheme("STR");

  sendRequest();

  redirect_headers_->setLocation("STR");
  EXPECT_CALL(connection_, ssl()).WillOnce(Return(ssl_connection));
  EXPECT_CALL(callbacks_.route_->route_entry_.internal_redirect_policy_,
              isCrossSchemeRedirectAllowed())
      .WillOnce(Return(true));
  EXPECT_CALL(callbacks_, clearRouteCache());
  EXPECT_CALL(callbacks_, recreateStream(_)).WillOnce(Return(true));
  response_decoder_->decodeHeaders(std::move(redirect_headers_), false);
  EXPECT_EQ(1U, cm_.thread_local_cluster_.cluster_.info_->stats_store_
                    .counter("STR")
                    .value());

  
  router_.onDestroy();
}