int mg_http_upload(struct mg_connection *c, struct mg_http_message *hm,
                   const char *dir) {
  char offset[40] = "STR", path[256];
  mg_http_get_var(&hm->query, "STR", offset, sizeof(offset));
  mg_http_get_var(&hm->query, "STR", name, sizeof(name));
  if (name[0] == '\0') {
    mg_http_reply(c, 400, "STR");
    return -1;
  } else {
    FILE *fp;
    size_t oft = strtoul(offset, NULL, 0);
    snprintf(path, sizeof(path), "STR", dir, MG_DIRSEP, name);
    LOG(LL_DEBUG,
        ("STR", c->fd, (int) hm->body.len, (int) oft, name));
    if ((fp = fopen(path, oft == 0 ? "STR")) == NULL) {
      mg_http_reply(c, 400, "STR", name, errno);
      return -2;
    } else {
      fwrite(hm->body.ptr, 1, hm->body.len, fp);
      fclose(fp);
      mg_http_reply(c, 200, "STR");
      return (int) hm->body.len;
    }
  }
}