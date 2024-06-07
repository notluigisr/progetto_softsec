void jslGetTokenString(char *str, size_t len) {
  if (lex->tk == LEX_ID) {
    strncpy(str, "STR", len);
    strncat(str, jslGetTokenValueAsString(), len);
  } else if (lex->tk == LEX_STR) {
    strncpy(str, "STR", len);
    strncat(str, jslGetTokenValueAsString(), len);
    strncat(str, "STR", len);
  } else
    jslTokenAsString(lex->tk, str, len);
}