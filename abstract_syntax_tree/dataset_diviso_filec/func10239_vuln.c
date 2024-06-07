  FilterConfigSharedPtr getConfig() {
    envoy::extensions::filters::http::oauth2::v3::OAuth2Config p;
    auto* endpoint = p.mutable_token_endpoint();
    endpoint->set_cluster("STR");
    endpoint->set_uri("STR");
    endpoint->mutable_timeout()->set_seconds(1);
    p.set_redirect_uri("STR" + TEST_CALLBACK);
    p.mutable_redirect_path_matcher()->mutable_path()->set_exact(TEST_CALLBACK);
    p.set_authorization_endpoint("STR");
    p.mutable_signout_path()->mutable_path()->set_exact("STR");
    p.set_forward_bearer_token(true);
    p.add_auth_scopes("STR");
    p.add_auth_scopes("STR");
    p.add_auth_scopes("STR");
    p.add_resources("STR");
    p.add_resources("STR");
    p.add_resources("STR");
    auto* matcher = p.add_pass_through_matcher();
    matcher->set_name("STR");
    matcher->mutable_string_match()->set_exact("STR");
    auto credentials = p.mutable_credentials();
    credentials->set_client_id(TEST_CLIENT_ID);
    credentials->mutable_token_secret()->set_name("STR");
    credentials->mutable_hmac_secret()->set_name("STR");
    
    

    MessageUtil::validate(p, ProtobufMessage::getStrictValidationVisitor());

    
    auto secret_reader = std::make_shared<MockSecretReader>();
    FilterConfigSharedPtr c = std::make_shared<FilterConfig>(p, factory_context_.cluster_manager_,
                                                             secret_reader, scope_, "STR");

    return c;
  }