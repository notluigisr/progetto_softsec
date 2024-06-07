Http2Stream::Provider::FD::FD(Http2Stream* stream, int options, int fd)
    : Http2Stream::Provider(stream, options) {
  CHECK(!stream->IsDestroyed());
  provider_.source.fd = fd;
  provider_.read_callback = Http2Stream::Provider::FD::OnRead;
}