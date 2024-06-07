static inline void openOptimized(sqlite3*& db) {
  sqlite3_open("STR", &db);

  std::string settings;
  for (const auto& setting : kMemoryDBSettings) {
    settings += "STR";
  }
  sqlite3_exec(db, settings.c_str(), nullptr, nullptr, nullptr);

  
  registerMathExtensions(db);
#if !defined(FREEBSD)
  registerStringExtensions(db);
#endif
#if !defined(SKIP_CARVER)
  registerOperationExtensions(db);
#endif
  registerFilesystemExtensions(db);
  registerHashingExtensions(db);
  registerEncodingExtensions(db);
}