Policy::Policy(CephContext* cct, const string& tenant,
	       const bufferlist& _text)
  : text(_text.to_str()) {
  StringStream ss(text.data());
  PolicyParser pp(cct, tenant, *this);
  auto pr = Reader{}.Parse<kParseNumbersAsStringsFlag |
			   kParseCommentsFlag>(ss, pp);
  if (!pr) {
    throw PolicyParseException(std::move(pr));
  }
}