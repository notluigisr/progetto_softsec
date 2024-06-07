peek_for_as4_capability (struct peer *peer, u_char length)
{
  struct stream *s = BGP_INPUT (peer);
  size_t orig_getp = stream_get_getp (s);
  size_t end = orig_getp + length;
  as_t as4 = 0;
  
  
  if (STREAM_READABLE(s) < length)
    return 0;

  if (BGP_DEBUG (as4, AS4))
    zlog_info ("STR"
                "STR",
	        peer->host, length);
  
  while (stream_get_getp(s) < end) 
    {
      u_char opt_type;
      u_char opt_length;
      
      
      if (stream_get_getp (s) + 2 > end)
        goto end;
      
      
      opt_type = stream_getc (s);
      opt_length = stream_getc (s);
      
      
      if (stream_get_getp (s) + opt_length > end)
        goto end;
      
      if (opt_type == BGP_OPEN_OPT_CAP)
        {
          unsigned long capd_start = stream_get_getp (s);
          unsigned long capd_end = capd_start + opt_length;
          
          assert (capd_end <= end);
          
	  while (stream_get_getp (s) < capd_end)
	    {
	      struct capability_header hdr;
	      
	      if (stream_get_getp (s) + 2 > capd_end)
                goto end;
              
              hdr.code = stream_getc (s);
              hdr.length = stream_getc (s);
              
	      if ((stream_get_getp(s) +  hdr.length) > capd_end)
		goto end;

	      if (hdr.code == CAPABILITY_CODE_AS4)
	        {
	          if (hdr.length != CAPABILITY_CODE_AS4_LEN)
	            goto end;
                  
	          if (BGP_DEBUG (as4, AS4))
	            zlog_info ("STR");
	          as4 = bgp_capability_as4 (peer, &hdr);
	          
	          goto end;
                }
              stream_forward_getp (s, hdr.length);
	    }
	}
    }

end:
  stream_set_getp (s, orig_getp);
  return as4;
}