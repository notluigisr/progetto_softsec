sec_to_pub_keyblock (kbnode_t sec_keyblock)
{
  kbnode_t pub_keyblock = NULL;
  kbnode_t ctx = NULL;
  kbnode_t secnode, pubnode;

  while ((secnode = walk_kbnode (sec_keyblock, &ctx, 0)))
    {
      if (secnode->pkt->pkttype == PKT_SECRET_KEY
          || secnode->pkt->pkttype == PKT_SECRET_SUBKEY)
	{
	  
	  PACKET *pkt;
          PKT_public_key *pk;

	  pkt = xtrycalloc (1, sizeof *pkt);
          pk = pkt? copy_public_key (NULL, secnode->pkt->pkt.public_key): NULL;
          if (!pk)
            {
              xfree (pkt);
	      release_kbnode (pub_keyblock);
              return NULL;
            }
	  if (secnode->pkt->pkttype == PKT_SECRET_KEY)
	    pkt->pkttype = PKT_PUBLIC_KEY;
	  else
	    pkt->pkttype = PKT_PUBLIC_SUBKEY;
	  pkt->pkt.public_key = pk;

	  pubnode = new_kbnode (pkt);
	}
      else
	{
	  pubnode = clone_kbnode (secnode);
	}

      if (!pub_keyblock)
	pub_keyblock = pubnode;
      else
	add_kbnode (pub_keyblock, pubnode);
    }

  return pub_keyblock;
}