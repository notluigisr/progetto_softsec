http_set_wait(http_t *http)		
{
  if (http->blocking)
  {
    http->wait_value = (int)(http->timeout_value * 1000);

    if (http->wait_value <= 0)
      http->wait_value = 60000;
  }
  else
    http->wait_value = 10000;
}