static inline const u32 *flow_keys_hash_start(const struct flow_keys *flow)
{
	const void *p = flow;

	BUILD_BUG_ON(FLOW_KEYS_HASH_OFFSET % sizeof(u32));
	return (const u32 *)(p + FLOW_KEYS_HASH_OFFSET);
}