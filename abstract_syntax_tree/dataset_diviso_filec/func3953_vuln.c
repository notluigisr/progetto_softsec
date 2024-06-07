  void RemoveZeroAdd(HAdd** add, HConstant** constant) {
    if (*add != NULL && (*constant)->Integer32Value() == 0) {
      (*add)->DeleteAndReplaceWith((*add)->left());
      (*constant)->DeleteAndReplaceWith(NULL);
    }
  }