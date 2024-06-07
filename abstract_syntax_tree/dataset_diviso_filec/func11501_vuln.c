bgp_attr_flag_invalid (struct peer *peer, u_int8_t attr_code, u_int8_t flags)
{
  u_int8_t mask = BGP_ATTR_FLAG_EXTLEN;
  
  
  if (attr_code > attr_flags_values_max)
    return 0;
  if (attr_flags_values[attr_code] == 0)
    return 0;
  
  
  if (!CHECK_FLAG (BGP_ATTR_FLAG_OPTIONAL, flags)
      && !CHECK_FLAG (BGP_ATTR_FLAG_TRANS, flags))
    {
      zlog (peer->log, LOG_ERR,
            "STR",
            LOOKUP (attr_str, attr_code), flags);
      return 1;
    }
  
  
  if (CHECK_FLAG (flags, BGP_ATTR_FLAG_PARTIAL))
    {
      if (!CHECK_FLAG (flags, BGP_ATTR_FLAG_OPTIONAL))
        {
          zlog (peer->log, LOG_ERR,
                "STR"
                "STR",
                 LOOKUP (attr_str, attr_code), flags);
          return 1;
        }
      if (CHECK_FLAG (flags, BGP_ATTR_FLAG_OPTIONAL)
          && !CHECK_FLAG (flags, BGP_ATTR_FLAG_TRANS))
        {
          zlog (peer->log, LOG_ERR,
                "STR"
                "STR",
                 LOOKUP (attr_str, attr_code), flags);
          return 1;
        }
    }
  
  
  if (CHECK_FLAG (flags, BGP_ATTR_FLAG_OPTIONAL)
      && CHECK_FLAG (flags, BGP_ATTR_FLAG_TRANS))
    SET_FLAG (mask, BGP_ATTR_FLAG_PARTIAL);
  
  if ((flags & ~attr_flags_values[attr_code])
      == attr_flags_values[attr_code])
    return 0;
  
  bgp_attr_flags_diagnose (peer, attr_code, attr_flags_values[attr_code],
                           flags);
  return 1;
}