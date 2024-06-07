DEFUN (no_neighbor_advertise_interval,
       no_neighbor_advertise_interval_cmd,
       NO_NEIGHBOR_CMD "STR",
       NO_STR
       NEIGHBOR_STR
       NEIGHBOR_ADDR_STR
       "STR")
{
  return peer_advertise_interval_vty (vty, argv[0], NULL, 0);
}