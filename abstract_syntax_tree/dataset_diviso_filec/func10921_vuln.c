int llhttp__after_headers_complete(llhttp_t* parser, const char* p,
                                   const char* endp) {
  int hasBody;

  hasBody = parser->flags & F_CHUNKED || parser->content_length > 0;
  if (parser->upgrade && (parser->method == HTTP_CONNECT ||
                          (parser->flags & F_SKIPBODY) || !hasBody)) {
    
    return 1;
  }

  if (parser->flags & F_SKIPBODY) {
    return 0;
  } else if (parser->flags & F_CHUNKED) {
    
    return 2;
  } else {
    if (!(parser->flags & F_CONTENT_LENGTH)) {
      if (!llhttp_message_needs_eof(parser)) {
        
        return 0;
      } else {
        
        return 4;
      }
    } else if (parser->content_length == 0) {
      
      return 0;
    } else {
      
      return 3;
    }
  }
}