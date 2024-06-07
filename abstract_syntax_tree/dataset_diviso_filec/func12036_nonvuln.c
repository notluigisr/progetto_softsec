pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
{
	if ((mutex->lock = malloc(sizeof(CRITICAL_SECTION))) == NULL)
		exit(ENOMEM);
	InitializeCriticalSection(mutex->lock);
	return 0;
}