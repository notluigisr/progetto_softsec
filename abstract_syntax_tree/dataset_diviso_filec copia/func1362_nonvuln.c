const char* llhttp_get_error_reason(const llhttp_t* parser) {
  return parser->reason;
}