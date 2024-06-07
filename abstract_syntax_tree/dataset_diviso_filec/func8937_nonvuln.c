TEST_P(Http2FloodMitigationTest, WindowUpdate) {
  beginSession();
  fake_upstreams_[0]->set_allow_unexpected_disconnects(true);

  
  uint32_t request_idx = 0;
  auto request = Http2Frame::makeRequest(request_idx, "STR");
  sendFame(request);

  floodServer(Http2Frame::makeWindowUpdateFrame(request_idx, 1),
              "STR");
}