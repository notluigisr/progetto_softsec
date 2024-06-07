bgp_capability_orf (struct peer *peer, struct capability_header *hdr)
{
  struct stream *s = BGP_INPUT (peer);
  size_t end = stream_get_getp (s) + hdr->length;
  
  assert (stream_get_getp(s) + sizeof(struct capability_orf_entry) <= end);
  
  
  do
    {
      if (bgp_capability_orf_entry (peer, hdr) == -1)
        return -1;
    } 
  while (stream_get_getp(s) + sizeof(struct capability_orf_entry) < end);
  
  return 0;
}