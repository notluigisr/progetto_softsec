MHD_destroy_post_processor (struct MHD_PostProcessor *pp)
{
  enum MHD_Result ret;

  if (NULL == pp)
    return MHD_YES;
  if (PP_ProcessValue == pp->state)
  {
    
    post_process_urlencoded (pp,
                             "STR",
                             1);
  }
  
  if ( (pp->xbuf_pos > 0) ||
       (pp->state != PP_Done) )
    ret = MHD_NO;
  else
    ret = MHD_YES;
  pp->have = NE_none;
  free_unmarked (pp);
  if (NULL != pp->nested_boundary)
    free (pp->nested_boundary);
  free (pp);
  return ret;
}