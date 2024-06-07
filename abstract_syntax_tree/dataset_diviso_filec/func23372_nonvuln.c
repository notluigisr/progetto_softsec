int audit_comparator(const u32 left, const u32 op, const u32 right)
{
	switch (op) {
	case AUDIT_EQUAL:
		return (left == right);
	case AUDIT_NOT_EQUAL:
		return (left != right);
	case AUDIT_LESS_THAN:
		return (left < right);
	case AUDIT_LESS_THAN_OR_EQUAL:
		return (left <= right);
	case AUDIT_GREATER_THAN:
		return (left > right);
	case AUDIT_GREATER_THAN_OR_EQUAL:
		return (left >= right);
	case AUDIT_BIT_MASK:
		return (left & right);
	case AUDIT_BIT_TEST:
		return ((left & right) == right);
	}
	BUG();
	return 0;
}