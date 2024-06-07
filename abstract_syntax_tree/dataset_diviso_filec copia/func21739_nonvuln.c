ecma_string_get_property_index (ecma_property_t property, 
                                jmem_cpointer_t prop_name_cp) 
{
  switch (ECMA_PROPERTY_GET_NAME_TYPE (property))
  {
    case ECMA_DIRECT_STRING_UINT:
    {
      return (uint32_t) prop_name_cp;
    }
    case ECMA_DIRECT_STRING_PTR:
    {
      ecma_string_t *prop_name_p = ECMA_GET_NON_NULL_POINTER (ecma_string_t, prop_name_cp);
      return ecma_string_get_array_index (prop_name_p);
    }
    default:
    {
      return ECMA_STRING_NOT_ARRAY_INDEX;
    }
  }
} 