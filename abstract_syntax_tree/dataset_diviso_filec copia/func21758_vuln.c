int
http_message_needs_eof (const http_parser *parser)
{
  if (parser->type == HTTP_REQUEST) {
    return 0;
  }

  
  if (parser->status_code / 100 == 1 || 
      parser->status_code == 204 ||     
      parser->status_code == 304 ||     
      parser->flags & F_SKIPBODY) {     
    return 0;
  }

  if ((parser->flags & F_CHUNKED) || parser->content_length != ULLONG_MAX) {
    return 0;
  }

  return 1;