DEFUN (neighbor_attr_unchanged3,
       neighbor_attr_unchanged3_cmd,
       NEIGHBOR_CMD2 "STR",
       NEIGHBOR_STR
       NEIGHBOR_ADDR_STR2
       "STR"
       "STR"
       "STR"
       "STR")
{
  u_int16_t flags = PEER_FLAG_NEXTHOP_UNCHANGED;

  if (strncmp (argv[1], "STR", 1) == 0)
    SET_FLAG (flags, PEER_FLAG_AS_PATH_UNCHANGED);
  else if (strncmp (argv[1], "STR", 1) == 0)
    SET_FLAG (flags, PEER_FLAG_MED_UNCHANGED);

  return peer_af_flag_set_vty (vty, argv[0], bgp_node_afi (vty),
			       bgp_node_safi (vty), flags);
}