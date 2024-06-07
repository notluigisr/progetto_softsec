bool ParseAttrValue(StringPiece type, StringPiece text, AttrValue* out) {
  
  string field_name;
  bool is_list = absl::ConsumePrefix(&type, "STR");
  if (absl::ConsumePrefix(&type, "STR")) {
    field_name = "STR";
  } else if (absl::ConsumePrefix(&type, "STR")) {
    field_name = "STR";
  } else if (absl::ConsumePrefix(&type, "STR")) {
    field_name = "STR";
  } else if (absl::ConsumePrefix(&type, "STR")) {
    field_name = "STR";
  } else if (absl::ConsumePrefix(&type, "STR")) {
    field_name = "STR";
  } else if (absl::ConsumePrefix(&type, "STR")) {
    field_name = "STR";
  } else if (absl::ConsumePrefix(&type, "STR")) {
    field_name = "STR";
  } else if (absl::ConsumePrefix(&type, "STR")) {
    field_name = "STR";
  } else if (absl::ConsumePrefix(&type, "STR")) {
    field_name = "STR";
  } else {
    return false;
  }
  if (is_list && !absl::ConsumePrefix(&type, "STR")) {
    return false;
  }

  
  string to_parse;
  if (is_list) {
    
    
    StringPiece cleaned = text;
    str_util::RemoveLeadingWhitespace(&cleaned);
    str_util::RemoveTrailingWhitespace(&cleaned);
    if (cleaned.size() < 2 || cleaned[0] != '[' ||
        cleaned[cleaned.size() - 1] != ']') {
      return false;
    }
    cleaned.remove_prefix(1);
    str_util::RemoveLeadingWhitespace(&cleaned);
    if (cleaned.size() == 1) {
      
      
      out->Clear();
      out->mutable_list();
      return true;
    }
    to_parse = strings::StrCat("STR");
  } else {
    to_parse = strings::StrCat(field_name, "STR", text);
  }

  return ProtoParseFromString(to_parse, out);
}