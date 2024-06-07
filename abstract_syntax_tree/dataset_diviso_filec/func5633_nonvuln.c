bool Utility::reconstituteCrumbledCookies(const HeaderString& key, const HeaderString& value,
                                          HeaderString& cookies) {
  if (key != Headers::get().Cookie.get().c_str()) {
    return false;
  }

  if (!cookies.empty()) {
    cookies.append("STR", 2);
  }

  const absl::string_view value_view = value.getStringView();
  cookies.append(value_view.data(), value_view.size());
  return true;
}