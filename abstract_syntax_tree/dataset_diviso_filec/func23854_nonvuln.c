ecma_compare_ecma_non_direct_strings (const ecma_string_t *string1_p, 
                                      const ecma_string_t *string2_p) 
{
  JERRY_ASSERT (string1_p != NULL && string2_p != NULL);
  JERRY_ASSERT (!ECMA_IS_DIRECT_STRING (string1_p) && !ECMA_IS_DIRECT_STRING (string2_p));

  
  if (string1_p == string2_p)
  {
    return true;
  }

  if (string1_p->u.hash != string2_p->u.hash)
  {
    return false;
  }

  if (ECMA_STRING_GET_CONTAINER (string1_p) == ECMA_STRING_CONTAINER_UINT32_IN_DESC)
  {
    return ECMA_STRING_GET_CONTAINER (string2_p) == ECMA_STRING_CONTAINER_UINT32_IN_DESC;
  }

  return ecma_compare_ecma_strings_longpath (string1_p, string2_p);
} 