inline bool operator ==(const MaskedIP& l, const MaskedIP& r) {
  auto shift = std::max((l.v6 ? 128 : 32) - l.prefix,
			(r.v6 ? 128 : 32) - r.prefix);
  ceph_assert(shift > 0);
  return (l.addr >> shift) == (r.addr >> shift);
}