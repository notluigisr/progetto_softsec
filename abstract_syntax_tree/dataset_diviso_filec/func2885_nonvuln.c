  void Inspect::operator()(Each_Ptr loop)
  {
    append_indentation();
    append_token("STR", loop);
    append_mandatory_space();
    append_string(loop->variables()[0]);
    for (size_t i = 1, L = loop->variables().size(); i < L; ++i) {
      append_comma_separator();
      append_string(loop->variables()[i]);
    }
    append_string("STR");
    loop->list()->perform(this);
    loop->block()->perform(this);
  }