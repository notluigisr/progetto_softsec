DEFUN (show_ipv6_mbgp_summary, 
       show_ipv6_mbgp_summary_cmd,
       "STR",
       SHOW_STR
       IPV6_STR
       MBGP_STR
       "STR")
{
  return bgp_show_summary_vty (vty, NULL, AFI_IP6, SAFI_MULTICAST);
}