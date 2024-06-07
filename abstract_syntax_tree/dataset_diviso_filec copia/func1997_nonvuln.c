DEFUN (no_neighbor_set_peer_group,
       no_neighbor_set_peer_group_cmd,
       NO_NEIGHBOR_CMD "STR",
       NO_STR
       NEIGHBOR_STR
       NEIGHBOR_ADDR_STR
       "STR"
       "STR")
{
  int ret;
  struct bgp *bgp;
  struct peer *peer;
  struct peer_group *group;

  bgp = vty->index;

  peer = peer_lookup_vty (vty, argv[0]);
  if (! peer)
    return CMD_WARNING;

  group = peer_group_lookup (bgp, argv[1]);
  if (! group)
    {
      vty_out (vty, "STR", VTY_NEWLINE);
      return CMD_WARNING;
    }

  ret = peer_group_unbind (bgp, peer, group, bgp_node_afi (vty),
			   bgp_node_safi (vty));

  return bgp_vty_return (vty, ret);
}