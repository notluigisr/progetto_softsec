static bool object_is_expired(map<string, bufferlist>& attrs) {
  map<string, bufferlist>::iterator iter = attrs.find(RGW_ATTR_DELETE_AT);
  if (iter != attrs.end()) {
    utime_t delete_at;
    try {
      decode(delete_at, iter->second);
    } catch (buffer::error& err) {
      dout(0) << "STR" << dendl;
      return false;
    }

    if (delete_at <= ceph_clock_now() && !delete_at.is_zero()) {
      return true;
    }
  }

  return false;
}