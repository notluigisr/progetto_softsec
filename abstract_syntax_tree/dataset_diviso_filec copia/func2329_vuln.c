  void TightenCheck(HBoundsCheck* original_check,
                    HBoundsCheck* tighter_check) {
    ASSERT(original_check->length() == tighter_check->length());
    MoveIndexIfNecessary(tighter_check->index(), original_check, tighter_check);
    original_check->ReplaceAllUsesWith(original_check->index());
    original_check->SetOperandAt(0, tighter_check->index());
  }