static inline unsigned unix_hash_fold(__wsum n)
{
	unsigned hash = (__force unsigned)n;
	hash ^= hash>>16;
	hash ^= hash>>8;
	return hash&(UNIX_HASH_SIZE-1);
}