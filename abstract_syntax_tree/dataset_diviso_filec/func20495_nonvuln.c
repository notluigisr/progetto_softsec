DEFUN (show_bgp_rsclient_summary,
       show_bgp_rsclient_summary_cmd,
       "STR",
       SHOW_STR
       BGP_STR
       "STR"
       "STR")
{
  return bgp_show_rsclient_summary_vty (vty, NULL, AFI_IP6, SAFI_UNICAST);
}