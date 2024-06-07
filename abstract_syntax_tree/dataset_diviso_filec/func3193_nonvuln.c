inline void Http2Session::GetTrailers(Http2Stream* stream, uint32_t* flags) {
  if (!stream->IsDestroyed() && stream->HasTrailers()) {
    Http2Stream::SubmitTrailers submit_trailers{this, stream, flags};
    stream->OnTrailers(submit_trailers);
  }
}