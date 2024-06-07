_dbus_validate_member (const DBusString  *str,
                       int                start,
                       int                len)
{
  const unsigned char *s;
  const unsigned char *end;
  const unsigned char *member;

  _dbus_assert (start >= 0);
  _dbus_assert (len >= 0);
  _dbus_assert (start <= _dbus_string_get_length (str));

  if (len > _dbus_string_get_length (str) - start)
    return FALSE;

  if (len > DBUS_MAXIMUM_NAME_LENGTH)
    return FALSE;

  if (len == 0)
    return FALSE;

  member = _dbus_string_get_const_data (str) + start;
  end = member + len;
  s = member;

  

  if (_DBUS_UNLIKELY (!VALID_INITIAL_NAME_CHARACTER (*s)))
    return FALSE;
  else
    ++s;

  while (s != end)
    {
      if (_DBUS_UNLIKELY (!VALID_NAME_CHARACTER (*s)))
        {
          return FALSE;
        }

      ++s;
    }

  return TRUE;
}