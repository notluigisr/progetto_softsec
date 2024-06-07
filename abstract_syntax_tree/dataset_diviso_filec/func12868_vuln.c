  const std::string& get_tenant() const {
    ceph_assert(t != Wildcard);
    return u.tenant;
  }