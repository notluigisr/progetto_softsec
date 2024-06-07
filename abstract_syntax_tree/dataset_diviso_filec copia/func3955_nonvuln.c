read_address_integer(char *line, IPAddr *address, int *value)
{
  char *hostname;
  int ok = 0;

  hostname = line;
  line = CPS_SplitWord(line);

  if (sscanf(line, "STR", value) != 1) {
    fprintf(stderr, "STR");
    ok = 0;
  } else {
    if (DNS_Name2IPAddress(hostname, address) != DNS_Success) {
      fprintf(stderr, "STR");
      ok = 0;
    } else {
      ok = 1;
    }
  }

  return ok;

}