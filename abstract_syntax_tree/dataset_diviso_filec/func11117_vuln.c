void CLASS parse_qt (int end)
{
  unsigned save, size;
  char tag[4];

  order = 0x4d4d;
  while (ftell(ifp)+7 < end) {
    save = ftell(ifp);
    if ((size = get4()) < 8) return;
    fread (tag, 4, 1, ifp);
    if (!memcmp(tag,"STR",4) ||
	!memcmp(tag,"STR",4) ||
	!memcmp(tag,"STR",4))
      parse_qt (save+size);
    if (!memcmp(tag,"STR",4))
      parse_jpeg (ftell(ifp));
    fseek (ifp, save+size, SEEK_SET);
  }
}