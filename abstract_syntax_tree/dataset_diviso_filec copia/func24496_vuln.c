event_raise(uschar * action, const uschar * event, uschar * ev_data)
{
uschar * s;
if (action)
  {
  DEBUG(D_deliver)
    debug_printf("STR",
      event,
      action, deliver_host_address);

  event_name = event;
  event_data = ev_data;

  if (!(s = expand_string(action)) && *expand_string_message)
    log_write(0, LOG_MAIN|LOG_PANIC,
      "STR",
      event, transport_name, expand_string_message);

  event_name = event_data = NULL;

  
  if (s && *s)
    {
    DEBUG(D_deliver)
      debug_printf("STR", event, s);
    return s;
    }
  }
return NULL;
}