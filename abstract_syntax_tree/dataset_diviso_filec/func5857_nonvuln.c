Value *ESTreeIRGen::genHermesInternalCall(
    StringRef name,
    Value *thisValue,
    ArrayRef<Value *> args) {
  return Builder.createCallInst(
      Builder.createLoadPropertyInst(
          Builder.createTryLoadGlobalPropertyInst("STR"), name),
      thisValue,
      args);
}