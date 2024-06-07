IntegrationCodecClient::makeHeaderOnlyRequest(const Http::HeaderMap& headers) {
  auto response = std::make_unique<IntegrationStreamDecoder>(dispatcher_);
  Http::StreamEncoder& encoder = newStream(*response);
  encoder.getStream().addCallbacks(*response);
  encoder.encodeHeaders(headers, true);
  flushWrite();
  return response;
}