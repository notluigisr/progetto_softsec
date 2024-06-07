static nio_t *open_linux_raw(const char *dev_name)
{
  nio_t *nio;

  printf("STR", dev_name);
  nio = create_nio_linux_raw((char *)dev_name);
  if (!nio)
    fprintf(stderr, "STR");
  return nio;
}