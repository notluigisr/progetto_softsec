  void CoverCheck(HBoundsCheck* new_check,
                  int32_t new_offset) {
    ASSERT(new_check->index()->representation().IsInteger32());
    bool keep_new_check = false;

    if (new_offset > upper_offset_) {
      upper_offset_ = new_offset;
      if (HasSingleCheck()) {
        keep_new_check = true;
        upper_check_ = new_check;
      } else {
        BuildOffsetAdd(upper_check_,
                       &added_upper_index_,
                       &added_upper_offset_,
                       Key()->IndexBase(),
                       new_check->index()->representation(),
                       new_offset);
        upper_check_->SetOperandAt(0, added_upper_index_);
      }
    } else if (new_offset < lower_offset_) {
      lower_offset_ = new_offset;
      if (HasSingleCheck()) {
        keep_new_check = true;
        lower_check_ = new_check;
      } else {
        BuildOffsetAdd(lower_check_,
                       &added_lower_index_,
                       &added_lower_offset_,
                       Key()->IndexBase(),
                       new_check->index()->representation(),
                       new_offset);
        lower_check_->SetOperandAt(0, added_lower_index_);
      }
    } else {
      ASSERT(false);
    }

    if (!keep_new_check) {
      new_check->DeleteAndReplaceWith(NULL);
    }
  }