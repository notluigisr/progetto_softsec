int llhttp__internal__c_load_header_state(
    llhttp__internal_t* state,
    const unsigned char* p,
    const unsigned char* endp) {
  return state->header_state;
}