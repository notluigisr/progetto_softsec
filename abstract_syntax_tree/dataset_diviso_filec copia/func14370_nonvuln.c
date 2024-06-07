int llhttp__internal__c_test_flags(
    llhttp__internal_t* state,
    const unsigned char* p,
    const unsigned char* endp) {
  return (state->flags & 128) == 128;
}