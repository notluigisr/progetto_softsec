print_p2r_iccpoweron (const unsigned char *msg, size_t msglen)
{
  print_p2r_header ("STR", msg, msglen);
  if (msglen < 10)
    return;
  printf ("STR", msg[7],
          msg[7] == 0? "STR":
          msg[7] == 1? "STR":
          msg[7] == 2? "STR":
          msg[7] == 3? "STR");
  print_pr_data (msg, msglen, 8);
}