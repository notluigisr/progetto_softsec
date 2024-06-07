void Http2FloodMitigationTest::startHttp2Session() {
  tcp_client_->write(Http2Frame::Preamble, false, false);

  
  auto settings = Http2Frame::makeEmptySettingsFrame();
  tcp_client_->write(std::string(settings), false, false);

  
  readFrame();

  
  settings = Http2Frame::makeEmptySettingsFrame(Http2Frame::SettingsFlags::ACK);
  tcp_client_->write(std::string(settings), false, false);

  
  readFrame();
  readFrame();
}