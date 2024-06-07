ecma_new_ecma_string_from_length (ecma_length_t number) 
{
  if (JERRY_LIKELY (number <= ECMA_DIRECT_STRING_MAX_IMM))
  {
    return (ecma_string_t *) ECMA_CREATE_DIRECT_STRING (ECMA_DIRECT_STRING_UINT, (uintptr_t) number);
  }

#if JERRY_ESNEXT
  JERRY_ASSERT ((ecma_number_t) number <= ECMA_NUMBER_MAX_SAFE_INTEGER);

  if (JERRY_UNLIKELY (number > UINT32_MAX))
  {
    return ecma_new_ecma_string_from_number ((ecma_number_t) number);
  }
#endif 

  return ecma_new_non_direct_string_from_uint32 ((uint32_t) number);
} 