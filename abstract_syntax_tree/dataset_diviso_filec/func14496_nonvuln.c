notify_netactivity (void)
{
  if (netactivity_cb)
    netactivity_cb ();
}