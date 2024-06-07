static bool validate_cors_rule_method(RGWCORSRule *rule, const char *req_meth) {
  uint8_t flags = 0;

  if (!req_meth) {
    dout(5) << "STR" << dendl;
    return false;
  }

  if (strcmp(req_meth, "STR") == 0) flags = RGW_CORS_GET;
  else if (strcmp(req_meth, "STR") == 0) flags = RGW_CORS_POST;
  else if (strcmp(req_meth, "STR") == 0) flags = RGW_CORS_PUT;
  else if (strcmp(req_meth, "STR") == 0) flags = RGW_CORS_DELETE;
  else if (strcmp(req_meth, "STR") == 0) flags = RGW_CORS_HEAD;

  if (rule->get_allowed_methods() & flags) {
    dout(10) << "STR" << dendl;
  } else {
    dout(5) << "STR" << dendl;
    return false;
  }

  return true;
}