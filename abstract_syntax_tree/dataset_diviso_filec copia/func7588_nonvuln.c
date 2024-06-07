static ssize_t store_user_show(struct kmem_cache *s, char *buf)
{
	return sprintf(buf, "STR", !!(s->flags & SLAB_STORE_USER));
}