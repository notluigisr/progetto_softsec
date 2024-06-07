Http2Stream::~Http2Stream() {
  if (session_ != nullptr) {
    session_->RemoveStream(id_);
    session_ = nullptr;
  }

  if (!object().IsEmpty())
    ClearWrap(object());
  persistent().Reset();
  CHECK(persistent().IsEmpty());
}