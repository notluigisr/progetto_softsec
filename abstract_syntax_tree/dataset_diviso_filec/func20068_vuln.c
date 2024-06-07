void Http2Stream::SubmitRstStream(const uint32_t code) {
  CHECK(!this->is_destroyed());
  code_ = code;

  
  
  
  
  
  

  
  
  
  
  if (session_->is_in_scope() &&
      !is_writable() && is_reading()) {
    session_->AddPendingRstStream(id_);
    return;
  }


  
  
  
  
  if (session_->SendPendingData() != 0) {
    session_->AddPendingRstStream(id_);
    return;
  }

  FlushRstStream();
}