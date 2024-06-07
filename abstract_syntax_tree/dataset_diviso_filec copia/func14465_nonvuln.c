DEFUN (show_bgp_instance_summary,
       show_bgp_instance_summary_cmd,
       "STR",
       SHOW_STR
       BGP_STR
       "STR"
       "STR"
       "STR")
{
  return bgp_show_summary_vty (vty, argv[0], AFI_IP6, SAFI_UNICAST);
}