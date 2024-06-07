SQLiteDBInstanceRef SQLiteDBManager::getConnection(bool primary) {
  auto& self = instance();
  WriteLock lock(self.create_mutex_);

  if (self.db_ == nullptr) {
    
    openOptimized(self.db_);
    self.connection_ = SQLiteDBInstanceRef(new SQLiteDBInstance(self.db_));
    attachVirtualTables(self.connection_);
  }

  
  if (primary) {
    return self.connection_;
  }

  
  auto instance = std::make_shared<SQLiteDBInstance>(self.db_, self.mutex_);
  if (!instance->isPrimary()) {
    attachVirtualTables(instance);
  }
  return instance;
}