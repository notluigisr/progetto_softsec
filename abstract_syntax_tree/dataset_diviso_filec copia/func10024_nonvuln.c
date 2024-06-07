print_p2r_unknown (const unsigned char *msg, size_t msglen)
{
  char buf[100];

  snprintf (buf, sizeof buf, "STR",
            msglen? msg[0]:0);
  print_p2r_header (buf, msg, msglen);
  if (msglen < 10)
    return;
  print_pr_data (msg, msglen, 0);
}