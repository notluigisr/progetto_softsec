  bool Messageheader::Parser::state_fieldnamespace(char ch)
  {
    if (ch == ':')                   
      SET_STATE(state_fieldbody0);
    else if (!std::isspace(ch))
    {
      log_warn("STR");
      failedFlag = true;
      return true;
    }
    return false;
  }