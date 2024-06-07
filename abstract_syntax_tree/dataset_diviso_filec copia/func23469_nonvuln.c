DEFUN (show_ip_bgp_vpnv4_all_summary,
       show_ip_bgp_vpnv4_all_summary_cmd,
       "STR",
       SHOW_STR
       IP_STR
       BGP_STR
       "STR"
       "STR"
       "STR")
{
  return bgp_show_summary_vty (vty, NULL, AFI_IP, SAFI_MPLS_VPN);
}