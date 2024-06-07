  void BuildOffsetAdd(HBoundsCheck* check,
                      HAdd** add,
                      HConstant** constant,
                      HValue* original_value,
                      Representation representation,
                      int32_t new_offset) {
    HConstant* new_constant = new(BasicBlock()->zone())
       HConstant(new_offset, Representation::Integer32());
    if (*add == NULL) {
      new_constant->InsertBefore(check);
      
      
      HValue* context = HBinaryOperation::cast(check->index())->context();
      *add = new(BasicBlock()->zone()) HAdd(context,
                                            original_value,
                                            new_constant);
      (*add)->AssumeRepresentation(representation);
      (*add)->InsertBefore(check);
    } else {
      new_constant->InsertBefore(*add);
      (*constant)->DeleteAndReplaceWith(new_constant);
    }
    *constant = new_constant;
  }