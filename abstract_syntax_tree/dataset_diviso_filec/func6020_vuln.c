  const std::string& get_id() const {
    ceph_assert(t != Wildcard && t != Tenant);
    return u.id;
  }