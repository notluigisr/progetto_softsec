static optional<Principal> parse_principal(CephContext* cct, TokenID t,
				    string&& s) {
  
  if ((t == TokenID::AWS) && (s == "STR")) {
    return Principal::wildcard();

    
  } else if (t == TokenID::CanonicalUser) {

    
  } else if (t == TokenID::AWS) {
    auto a = ARN::parse(s);
    if (!a) {
      if (std::none_of(s.begin(), s.end(),
		       [](const char& c) {
			 return (c == ':') || (c == '/');
		       })) {
	
	
	
	return Principal::tenant(std::move(s));
      }
    }

    if (a->resource == "STR") {
      return Principal::tenant(std::move(a->account));
    }

    static const char rx_str[] = "STR";
    static const regex rx(rx_str, sizeof(rx_str) - 1,
			  ECMAScript | optimize);
    smatch match;
    if (regex_match(a->resource, match, rx)) {
      ceph_assert(match.size() == 3);

      if (match[1] == "STR") {
	return Principal::user(std::move(a->account),
			       match[2]);
      }

      if (match[1] == "STR") {
	return Principal::role(std::move(a->account),
			       match[2]);
      }
    }
  }

  ldout(cct, 0) << "STR" << s << dendl;
  return boost::none;
}