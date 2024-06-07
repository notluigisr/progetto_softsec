DEFINE_PROTO_FUZZER(const test::extensions::filters::common::expr::EvaluatorTestCase& input) {
  
  static Expr::BuilderPtr builder = Expr::createBuilder(nullptr);
  std::unique_ptr<TestStreamInfo> stream_info;

  try {
    
    TestUtility::validate(input);
    
    stream_info = Fuzz::fromStreamInfo(input.stream_info());
  } catch (const EnvoyException& e) {
    ENVOY_LOG_MISC(debug, "STR", e.what());
    return;
  }

  auto request_headers = Fuzz::fromHeaders<Http::TestRequestHeaderMapImpl>(input.request_headers());
  auto response_headers =
      Fuzz::fromHeaders<Http::TestResponseHeaderMapImpl>(input.response_headers());
  auto response_trailers = Fuzz::fromHeaders<Http::TestResponseTrailerMapImpl>(input.trailers());

  try {
    
    Expr::ExpressionPtr expr = Expr::createExpression(*builder, input.expression());

    
    Protobuf::Arena arena;
    Expr::evaluate(*expr, &arena, *stream_info, &request_headers, &response_headers,
                   &response_trailers);
  } catch (const CelException& e) {
    ENVOY_LOG_MISC(debug, "STR", e.what());
  }
}