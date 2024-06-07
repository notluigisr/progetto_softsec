DEFUN (show_ip_bgp_neighbors,
       show_ip_bgp_neighbors_cmd,
       "STR",
       SHOW_STR
       IP_STR
       BGP_STR
       "STR")
{
  return bgp_show_neighbor_vty (vty, NULL, show_all, NULL);
}