DEFUN (no_neighbor_attr_unchanged1,
       no_neighbor_attr_unchanged1_cmd,
       NO_NEIGHBOR_CMD2 "STR",
       NO_STR
       NEIGHBOR_STR
       NEIGHBOR_ADDR_STR2
       "STR"
       "STR"
       "STR"
       "STR")
{
  u_int16_t flags = 0;

  if (strncmp (argv[1], "STR", 1) == 0)
    SET_FLAG (flags, PEER_FLAG_AS_PATH_UNCHANGED);
  else if (strncmp (argv[1], "STR", 1) == 0)
    SET_FLAG (flags, PEER_FLAG_NEXTHOP_UNCHANGED);
  else if (strncmp (argv[1], "STR", 1) == 0)
    SET_FLAG (flags, PEER_FLAG_MED_UNCHANGED);

  return peer_af_flag_unset_vty (vty, argv[0], bgp_node_afi (vty),
				 bgp_node_safi (vty), flags);
}