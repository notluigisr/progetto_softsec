  Item** addr(uint i)
  {
    return ref && result_type() == ROW_RESULT ? (*ref)->addr(i) : 0;
  }