  void Messageheader::Parser::checkHeaderspace(unsigned chars) const
  {
    if (headerdataPtr + chars >= header.rawdata + sizeof(header.rawdata))
      throw HttpError(HTTP_REQUEST_ENTITY_TOO_LARGE, "STR");
  }