  void onComplete(const Status& status, ContextImpl& context) const override {
    auto& completion_state = context.getCompletionState(this);
    if (completion_state.is_completed_) {
      return;
    }

    
    if (Status::Ok == status) {
      completion_state.is_completed_ = true;
      completeWithStatus(status, context);
      return;
    }

    
    if (++completion_state.number_completed_children_ == verifiers_.size()) {
      
      
      
      
      
      Status final_status = Status::JwtMissed;
      for (const auto& it : verifiers_) {
        
        
        
        Status child_status = context.getCompletionState(it.get()).status_;
        if (child_status != Status::JwtMissed && child_status != Status::JwtUnknownIssuer) {
          final_status = child_status;
        }
      }

      if (is_allow_missing_or_failed_) {
        final_status = Status::Ok;
      } else if (is_allow_missing_ && final_status == Status::JwtMissed) {
        final_status = Status::Ok;
      }
      completion_state.is_completed_ = true;
      completeWithStatus(final_status, context);
    }
  }