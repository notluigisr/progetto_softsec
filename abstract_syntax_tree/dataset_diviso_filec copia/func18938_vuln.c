lexer_compare_identifier_to_string (const lexer_lit_location_t *left_p, 
                                    const uint8_t *right_p, 
                                    size_t size) 
{
  if (left_p->length != size)
  {
    return false;
  }

  if (!left_p->has_escape)
  {
    return memcmp (left_p->char_p, right_p, size) == 0;
  }

  return lexer_compare_identifier_to_chars (left_p->char_p, right_p, size);
} 