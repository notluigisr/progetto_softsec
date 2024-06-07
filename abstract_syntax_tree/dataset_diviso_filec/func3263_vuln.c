transientObjectPutErrorMessage(Runtime *runtime, Handle<> base, SymbolID id) {
  
  
  StringView propName =
      runtime->getIdentifierTable().getStringView(runtime, id);
  Handle<StringPrimitive> baseType =
      runtime->makeHandle(vmcast<StringPrimitive>(typeOf(runtime, base)));
  StringView baseTypeAsString =
      StringPrimitive::createStringView(runtime, baseType);
  MutableHandle<StringPrimitive> valueAsString{runtime};
  if (base->isSymbol()) {
    
    auto str = symbolDescriptiveString(runtime, Handle<SymbolID>::vmcast(base));
    if (str != ExecutionStatus::EXCEPTION) {
      valueAsString = *str;
    } else {
      runtime->clearThrownValue();
      valueAsString = StringPrimitive::createNoThrow(
          runtime, "STR");
    }
  } else {
    auto str = toString_RJS(runtime, base);
    assert(
        str != ExecutionStatus::EXCEPTION &&
        "STR");
    valueAsString = std::move(*str);
  }
  StringView valueAsStringPrintable =
      StringPrimitive::createStringView(runtime, valueAsString);

  SmallU16String<32> tmp;
  return runtime->raiseTypeError(
      TwineChar16("STR" +
      baseTypeAsString.getUTF16Ref(tmp) + "STR" +
      valueAsStringPrintable.getUTF16Ref(tmp) + "STR");
}