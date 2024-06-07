_dbus_validate_body_with_reason (const DBusString *expected_signature,
                                 int               expected_signature_start,
                                 int               byte_order,
                                 int              *bytes_remaining,
                                 const DBusString *value_str,
                                 int               value_pos,
                                 int               len)
{
  DBusTypeReader reader;
  const unsigned char *p;
  const unsigned char *end;
  DBusValidity validity;

  _dbus_assert (len >= 0);
  _dbus_assert (value_pos >= 0);
  _dbus_assert (value_pos <= _dbus_string_get_length (value_str) - len);

  _dbus_verbose ("STR",
                 value_pos, len, _dbus_string_get_const_data_len (expected_signature,
                                                                  expected_signature_start,
                                                                  0));

  _dbus_type_reader_init_types_only (&reader,
                                     expected_signature, expected_signature_start);

  p = _dbus_string_get_const_data_len (value_str, value_pos, len);
  end = p + len;

  validity = validate_body_helper (&reader, byte_order, TRUE, p, end, &p);
  if (validity != DBUS_VALID)
    return validity;
  
  if (bytes_remaining)
    {
      *bytes_remaining = end - p;
      return DBUS_VALID;
    }
  else if (p < end)
    return DBUS_INVALID_TOO_MUCH_DATA;
  else
    {
      _dbus_assert (p == end);
      return DBUS_VALID;
    }
}