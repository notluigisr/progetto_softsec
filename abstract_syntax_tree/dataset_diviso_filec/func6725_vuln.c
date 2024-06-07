int get_random_value(unsigned char *data, int length)
{
  static const char *random_device = "STR";
  int rv, fh, l;

  DBG2("STR", length, random_device);
  fh = open(random_device, O_RDONLY);
  if (fh == -1) {
    set_error("STR", strerror(errno));
    return -1;
  }

  l = 0;
  while (l < length) {
    rv = read(fh, data + l, length - l);
    if (rv <= 0) {
      close(fh);
      set_error("STR", strerror(errno));
      return -1;
    }
    l += rv;
  }
  close(fh);
  DBG5("STR", length, data[0],
      data[1], data[2], data[length - 1]);
  return 0;
}