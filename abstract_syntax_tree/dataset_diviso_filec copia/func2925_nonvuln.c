int llhttp__internal__c_mul_add_content_length(
    llhttp__internal_t* state,
    const unsigned char* p,
    const unsigned char* endp,
    int match) {
  
  if (state->content_length > 0xffffffffffffffffULL / 16) {
    return 1;
  }
  
  state->content_length *= 16;
  
  
  if (match >= 0) {
    if (state->content_length > 0xffffffffffffffffULL - match) {
      return 1;
    }
  } else {
    if (state->content_length < 0ULL - match) {
      return 1;
    }
  }
  state->content_length += match;
  return 0;
}