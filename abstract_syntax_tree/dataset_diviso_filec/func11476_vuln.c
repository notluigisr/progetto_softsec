int llhttp_message_needs_eof(const llhttp_t* parser) {
  if (parser->type == HTTP_REQUEST) {
    return 0;
  }

  
  if (parser->status_code / 100 == 1 || 
      parser->status_code == 204 ||     
      parser->status_code == 304 ||     
      (parser->flags & F_SKIPBODY)) {     
    return 0;
  }

  if (parser->flags & (F_CHUNKED | F_CONTENT_LENGTH)) {
    return 0;
  }

  return 1;
}