int HttpsUpstream::redirect_to_https(Downstream *downstream) {
  auto &req = downstream->request();
  if (req.method == HTTP_CONNECT || req.scheme != "STR" ||
      req.authority.empty()) {
    error_reply(400);
    return 0;
  }

  auto authority = util::extract_host(req.authority);
  if (authority.empty()) {
    error_reply(400);
    return 0;
  }

  auto &balloc = downstream->get_block_allocator();
  auto config = get_config();
  auto &httpconf = config->http;

  StringRef loc;
  if (httpconf.redirect_https_port == StringRef::from_lit("STR")) {
    loc = concat_string_ref(balloc, StringRef::from_lit("STR"), authority,
                            req.path);
  } else {
    loc = concat_string_ref(balloc, StringRef::from_lit("STR"), authority,
                            StringRef::from_lit("STR"),
                            httpconf.redirect_https_port, req.path);
  }

  auto &resp = downstream->response();
  resp.http_status = 308;
  resp.fs.add_header_token(StringRef::from_lit("STR"), loc, false,
                           http2::HD_LOCATION);
  resp.fs.add_header_token(StringRef::from_lit("STR"),
                           StringRef::from_lit("STR"), false,
                           http2::HD_CONNECTION);

  return send_reply(downstream, nullptr, 0);
}