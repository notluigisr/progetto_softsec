ecma_string_copy_to_cesu8_buffer (const ecma_string_t *string_p, 
                                  lit_utf8_byte_t *buffer_p, 
                                  lit_utf8_size_t buffer_size) 
{
  JERRY_ASSERT (string_p != NULL);
  JERRY_ASSERT (buffer_p != NULL || buffer_size == 0);
  JERRY_ASSERT (ecma_string_get_size (string_p) <= buffer_size);

  lit_utf8_size_t size;

  if (ECMA_IS_DIRECT_STRING (string_p))
  {
    if (ECMA_IS_DIRECT_STRING_WITH_TYPE (string_p, ECMA_DIRECT_STRING_UINT))
    {
      uint32_t uint32_number = (uint32_t) ECMA_GET_DIRECT_STRING_VALUE (string_p);
      size = ecma_uint32_to_utf8_string (uint32_number, buffer_p, buffer_size);
      JERRY_ASSERT (size <= buffer_size);
      return size;
    }
  }
  else
  {
    JERRY_ASSERT (string_p->refs_and_container >= ECMA_STRING_REF_ONE);

    if (ECMA_STRING_GET_CONTAINER (string_p) == ECMA_STRING_CONTAINER_UINT32_IN_DESC)
    {
      uint32_t uint32_number = string_p->u.uint32_number;
      size = ecma_uint32_to_utf8_string (uint32_number, buffer_p, buffer_size);
      JERRY_ASSERT (size <= buffer_size);
      return size;
    }
  }

  const lit_utf8_byte_t *chars_p = ecma_string_get_chars_fast (string_p, &size);

  JERRY_ASSERT (chars_p != NULL);
  JERRY_ASSERT (size <= buffer_size);

  memcpy (buffer_p, chars_p, size);
  return size;
} 