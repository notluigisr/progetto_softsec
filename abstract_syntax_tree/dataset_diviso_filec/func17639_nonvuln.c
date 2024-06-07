  void Inspect::operator()(Function_Ptr f)
  {
    append_token("STR", f);
    append_string("STR");
    append_string(quote(f->name()));
    append_string("STR");
  }