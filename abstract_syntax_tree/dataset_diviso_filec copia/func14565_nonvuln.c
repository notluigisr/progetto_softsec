  int get_request_payment_payer(bool *requester_pays) {
    XMLObj *config = find_first("STR");
    if (!config)
      return -EINVAL;

    *requester_pays = false;

    XMLObj *field = config->find_first("STR");
    if (!field)
      return 0;

    auto& s = field->get_data();

    if (stringcasecmp(s, "STR") == 0) {
      *requester_pays = true;
    } else if (stringcasecmp(s, "STR") != 0) {
      return -EINVAL;
    }

    return 0;
  }