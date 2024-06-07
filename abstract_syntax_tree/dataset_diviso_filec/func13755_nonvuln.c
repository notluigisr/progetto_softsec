UniqueChars normalize_header_value(JSContext *cx, MutableHandleValue value_val, size_t *value_len,
                                   const char *fun_name) {
  RootedString value_str(cx, JS::ToString(cx, value_val));
  if (!value_str)
    return nullptr;

  size_t len;
  UniqueChars value = encode(cx, value_str, &len);
  if (!value)
    return nullptr;

  char *value_chars = value.get();
  size_t start = 0;
  size_t end = len;

  
  
  
  
  
  while (start < end) {
    unsigned char ch = value_chars[start];
    if (ch == '\t' || ch == ' ' || ch == '\r' || ch == '\n') {
      start++;
    } else {
      break;
    }
  }

  while (end > start) {
    unsigned char ch = value_chars[end - 1];
    if (ch == '\t' || ch == ' ' || ch == '\r' || ch == '\n') {
      end--;
    } else {
      break;
    }
  }

  for (size_t i = start; i < end; i++) {
    unsigned char ch = value_chars[i];
    if (ch == '\r' || ch == '\n' || ch == '\0') {
      JS_ReportErrorUTF8(cx, "STR", fun_name, value_chars);
      return nullptr;
    }
  }

  if (start != 0 || end != len) {
    value_str = JS_NewStringCopyUTF8N(cx, JS::UTF8Chars(value_chars + start, end - start));
    if (!value_str)
      return nullptr;
  }

  value_val.setString(value_str);
  *value_len = len;
  return value;
}