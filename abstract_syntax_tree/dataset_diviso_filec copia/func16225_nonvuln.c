DEFUN (address_family_ipv6,
       address_family_ipv6_cmd,
       "STR",
       "STR"
       "STR")
{
  vty->node = BGP_IPV6_NODE;
  return CMD_SUCCESS;
}