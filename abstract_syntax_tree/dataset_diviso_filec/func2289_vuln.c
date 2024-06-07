  void MoveIndexIfNecessary(HValue* index_raw,
                            HBoundsCheck* insert_before,
                            HInstruction* end_of_scan_range) {
    ASSERT(index_raw->IsAdd() || index_raw->IsSub());
    HBinaryOperation* index =
        HArithmeticBinaryOperation::cast(index_raw);
    HValue* left_input = index->left();
    HValue* right_input = index->right();
    bool must_move_index = false;
    bool must_move_left_input = false;
    bool must_move_right_input = false;
    for (HInstruction* cursor = end_of_scan_range; cursor != insert_before;) {
      if (cursor == left_input) must_move_left_input = true;
      if (cursor == right_input) must_move_right_input = true;
      if (cursor == index) must_move_index = true;
      if (cursor->previous() == NULL) {
        cursor = cursor->block()->dominator()->end();
      } else {
        cursor = cursor->previous();
      }
    }

    
    
    if (must_move_left_input) {
      HConstant::cast(left_input)->Unlink();
      HConstant::cast(left_input)->InsertBefore(index);
    }
    if (must_move_right_input) {
      HConstant::cast(right_input)->Unlink();
      HConstant::cast(right_input)->InsertBefore(index);
    }
  }