bool operator <(const ARN& l, const ARN& r) {
  return ((l.partition < r.partition) ||
	  (l.service < r.service) ||
	  (l.region < r.region) ||
	  (l.account < r.account) ||
	  (l.resource < r.resource));
}