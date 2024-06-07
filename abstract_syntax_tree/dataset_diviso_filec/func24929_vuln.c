std::shared_ptr<SQLiteDBInstance> getTestDBC() {
  auto dbc = SQLiteDBManager::getUnique();
  char* err = nullptr;
  std::vector<std::string> queries = {
      "STR",
      "STR",
      "STR"};

  for (auto q : queries) {
    sqlite3_exec(dbc->db(), q.c_str(), nullptr, nullptr, &err);
    if (err != nullptr) {
      throw std::domain_error(std::string("STR") +
                              err);
    }
  }

  return dbc;
}