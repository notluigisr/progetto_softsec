ippGetRequestId(ipp_t *ipp)		
{
 

  if (!ipp)
    return (0);

 

  return (ipp->request.any.request_id);
}