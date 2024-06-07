bool Condition::eval(const Environment& env) const {
  auto i = env.find(key);
  if (op == TokenID::Null) {
    return i == env.end() ? true : false;
  }

  if (i == env.end()) {
    return ifexists;
  }
  const auto& s = i->second;

  switch (op) {
    
  case TokenID::StringEquals:
    return orrible(std::equal_to<std::string>(), s, vals);

  case TokenID::StringNotEquals:
    return orrible(ceph::not_fn(std::equal_to<std::string>()),
		   s, vals);

  case TokenID::StringEqualsIgnoreCase:
    return orrible(ci_equal_to(), s, vals);

  case TokenID::StringNotEqualsIgnoreCase:
    return orrible(ceph::not_fn(ci_equal_to()), s, vals);

  case TokenID::StringLike:
    return orrible(string_like(), s, vals);

  case TokenID::StringNotLike:
    return orrible(ceph::not_fn(string_like()), s, vals);

    
  case TokenID::NumericEquals:
    return shortible(std::equal_to<double>(), as_number, s, vals);

  case TokenID::NumericNotEquals:
    return shortible(ceph::not_fn(std::equal_to<double>()),
		     as_number, s, vals);


  case TokenID::NumericLessThan:
    return shortible(std::less<double>(), as_number, s, vals);


  case TokenID::NumericLessThanEquals:
    return shortible(std::less_equal<double>(), as_number, s, vals);

  case TokenID::NumericGreaterThan:
    return shortible(std::greater<double>(), as_number, s, vals);

  case TokenID::NumericGreaterThanEquals:
    return shortible(std::greater_equal<double>(), as_number, s, vals);

    
  case TokenID::DateEquals:
    return shortible(std::equal_to<ceph::real_time>(), as_date, s, vals);

  case TokenID::DateNotEquals:
    return shortible(ceph::not_fn(std::equal_to<ceph::real_time>()),
		     as_date, s, vals);

  case TokenID::DateLessThan:
    return shortible(std::less<ceph::real_time>(), as_date, s, vals);


  case TokenID::DateLessThanEquals:
    return shortible(std::less_equal<ceph::real_time>(), as_date, s, vals);

  case TokenID::DateGreaterThan:
    return shortible(std::greater<ceph::real_time>(), as_date, s, vals);

  case TokenID::DateGreaterThanEquals:
    return shortible(std::greater_equal<ceph::real_time>(), as_date, s,
		     vals);

    
  case TokenID::Bool:
    return shortible(std::equal_to<bool>(), as_bool, s, vals);

    
  case TokenID::BinaryEquals:
    return shortible(std::equal_to<ceph::bufferlist>(), as_binary, s,
		     vals);

    
  case TokenID::IpAddress:
    return shortible(std::equal_to<MaskedIP>(), as_network, s, vals);

  case TokenID::NotIpAddress:
    return shortible(ceph::not_fn(std::equal_to<MaskedIP>()), as_network, s,
		     vals);

#if 0
    
    TokenID::ArnEquals, TokenID::ArnNotEquals, TokenID::ArnLike,
      TokenID::ArnNotLike,
#endif

  default:
    return false;
  }
}