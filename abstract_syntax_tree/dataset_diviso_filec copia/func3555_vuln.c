static inline struct sock *pop_stack(void)
{
	struct sock *p = gc_current;
	gc_current = unix_sk(p)->gc_tree;
	return p;
}