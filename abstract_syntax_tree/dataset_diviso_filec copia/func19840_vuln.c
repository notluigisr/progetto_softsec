int main(int argc, char** argv)
{
  int sck;
  int dis;
  struct sockaddr_un sa;
  size_t len;
  char* p;
  char* display;

  if (argc != 1)
  {
    printf("STR");
    printf("STR");
    return 0;
  }

  display = getenv("STR");
  if (display == 0)
  {
    printf("STR");
    return 1;
  }
  dis = strtol(display + 1, &p, 10);
  memset(&sa, 0, sizeof(sa));
  sa.sun_family = AF_UNIX;
  sprintf(sa.sun_path, "STR", dis);
  if (access(sa.sun_path, F_OK) != 0)
  {
    printf("STR");
    return 1;
  }
  sck = socket(PF_UNIX, SOCK_DGRAM, 0);
  len = sizeof(sa);
  if (sendto(sck, "STR", 4, 0, (struct sockaddr*)&sa, len) > 0)
  {
    printf("STR");
  }
  return 0;
}