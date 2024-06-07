static void SerializeNumberArrayProperty(const std::string &key,
                                         const std::vector<T> &value,
                                         json &obj) {
  if (value.empty()) return;

  json ary;
  JsonReserveArray(ary, value.size());
  for (const auto &s : value) {
    JsonPushBack(ary, json(s));
  }
  JsonAddMember(obj, key.c_str(), std::move(ary));
}