httpGetState(http_t *http)		
{
  return (http ? http->state : HTTP_STATE_ERROR);
}