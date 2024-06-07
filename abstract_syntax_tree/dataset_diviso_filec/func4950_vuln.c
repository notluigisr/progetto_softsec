bgp_capability_vty_out (struct vty *vty, struct peer *peer)
{
  char *pnt;
  char *end;
  struct capability cap;

  pnt = peer->notify.data;
  end = pnt + peer->notify.length;

  while (pnt < end)
    {
      memcpy(&cap, pnt, sizeof(struct capability));

      if (pnt + 2 > end)
	return;
      if (pnt + (cap.length + 2) > end)
	return;

      if (cap.code == CAPABILITY_CODE_MP)
	{
	  vty_out (vty, "STR");

	  switch (ntohs (cap.mpc.afi))
	    {
	    case AFI_IP:
	      vty_out (vty, "STR");
	      break;
	    case AFI_IP6:
	      vty_out (vty, "STR");
	      break;
	    default:
	      vty_out (vty, "STR", ntohs (cap.mpc.afi));
	      break;
	    }
	  switch (cap.mpc.safi)
	    {
	    case SAFI_UNICAST:
	      vty_out (vty, "STR");
	      break;
	    case SAFI_MULTICAST:
	      vty_out (vty, "STR");
	      break;
	    case SAFI_UNICAST_MULTICAST:
	      vty_out (vty, "STR");
	      break;
	    case BGP_SAFI_VPNV4:
	      vty_out (vty, "STR");
	      break;
	    default:
	      vty_out (vty, "STR", cap.mpc.safi);
	      break;
	    }
	  vty_out (vty, "STR", VTY_NEWLINE);
	}
      else if (cap.code >= 128)
	vty_out (vty, "STR",
		 cap.code);
      else
	vty_out (vty, "STR", 
		 cap.code);

      pnt += cap.length + 2;
    }
}