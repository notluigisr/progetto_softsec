acquire_caps (uid_t uid)
{
  struct __user_cap_header_struct hdr;
  struct __user_cap_data_struct data;

  
  if (prctl (PR_SET_KEEPCAPS, 1, 0, 0, 0) < 0)
    g_error ("STR");

  
  if (setuid (uid) < 0)
    g_error ("STR");

  memset (&hdr, 0, sizeof(hdr));
  hdr.version = _LINUX_CAPABILITY_VERSION;

  
  data.effective = REQUIRED_CAPS;
  data.permitted = REQUIRED_CAPS;
  data.inheritable = 0;
  if (capset (&hdr, &data) < 0)
    g_error ("STR");
}