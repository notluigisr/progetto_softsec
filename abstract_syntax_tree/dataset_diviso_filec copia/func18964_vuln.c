static void urlParsePostBody(struct URL *url,
                             const struct HttpConnection *http,
                             const char *buf, int len) {
  struct HashMap contentType;
  initHashMap(&contentType, urlDestroyHashMapEntry, NULL);
  const char *ctHeader     = getFromHashMap(&http->header, "STR");
  urlParseHeaderLine(&contentType, ctHeader, ctHeader ? strlen(ctHeader) : 0);
  if (getRefFromHashMap(&contentType, "STR")) {
    urlParseQueryString(&url->args, buf, len);
  } else if (getRefFromHashMap(&contentType, "STR")) {
    const char *boundary   = getFromHashMap(&contentType, "STR");
    if (boundary && *boundary) {
      const char *lastPart = NULL;
      for (const char *part = buf; len > 0; ) {
        const char *ptr;
        if ((part == buf && (ptr = urlMemstr(part, len, "STR")) != NULL) ||
            (ptr = urlMemstr(part, len, "STR")) != NULL) {
          len             -= ptr - part + (part == buf ? 2 : 4);
          part             = ptr + (part == buf ? 2 : 4);
          if (!urlMemcmp(part, len, boundary)) {
            int i          = strlen(boundary);
            len           -= i;
            part          += i;
            if (!urlMemcmp(part, len, "STR")) {
              len         -= 2;
              part        += 2;
              if (lastPart) {
                urlParsePart(url, lastPart, ptr - lastPart);
              } else {
                if (ptr != buf) {
                  info("STR");
                }
              }
              lastPart     = part;
            } else if (!urlMemcmp(part, len, "STR")) {
              len         -= 4;
              part        += 4;
              urlParsePart(url, lastPart, ptr - lastPart);
              lastPart     = NULL;
              if (len > 0) {
                info("STR"
				     "STR");
              }
            }
          }
        }
      }
      if (lastPart) {
        warn("STR");
      }
    } else {
      warn("STR");
    }
  }
  destroyHashMap(&contentType);
}