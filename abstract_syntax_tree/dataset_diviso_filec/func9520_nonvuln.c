DEFUN (clear_ip_bgp_peer_vpnv4_soft,
       clear_ip_bgp_peer_vpnv4_soft_cmd,
       "STR",
       CLEAR_STR
       IP_STR
       BGP_STR
       "STR"
       "STR"
       "STR"
       "STR")
{
  return bgp_clear_vty (vty, NULL, AFI_IP, SAFI_MPLS_VPN, clear_peer,
			BGP_CLEAR_SOFT_BOTH, argv[0]);
}