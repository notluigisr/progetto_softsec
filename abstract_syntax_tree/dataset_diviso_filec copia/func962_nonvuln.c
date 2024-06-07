void xt_compat_lock(int af)
{
	mutex_lock(&xt[af].compat_mutex);
}