static int do_cpu_nanosleep(const clockid_t which_clock, int flags,
			    struct timespec *rqtp, struct itimerspec *it)
{
	struct k_itimer timer;
	int error;

	
	memset(&timer, 0, sizeof timer);
	spin_lock_init(&timer.it_lock);
	timer.it_clock = which_clock;
	timer.it_overrun = -1;
	error = posix_cpu_timer_create(&timer);
	timer.it_process = current;
	if (!error) {
		static struct itimerspec zero_it;

		memset(it, 0, sizeof *it);
		it->it_value = *rqtp;

		spin_lock_irq(&timer.it_lock);
		error = posix_cpu_timer_set(&timer, flags, it, NULL);
		if (error) {
			spin_unlock_irq(&timer.it_lock);
			return error;
		}

		while (!signal_pending(current)) {
			if (timer.it.cpu.expires.sched == 0) {
				
				spin_unlock_irq(&timer.it_lock);
				return 0;
			}

			
			__set_current_state(TASK_INTERRUPTIBLE);
			spin_unlock_irq(&timer.it_lock);
			schedule();
			spin_lock_irq(&timer.it_lock);
		}

		
		sample_to_timespec(which_clock, timer.it.cpu.expires, rqtp);
		posix_cpu_timer_set(&timer, 0, &zero_it, it);
		spin_unlock_irq(&timer.it_lock);

		if ((it->it_value.tv_sec | it->it_value.tv_nsec) == 0) {
			
			return 0;
		}

		error = -ERESTART_RESTARTBLOCK;
	}

	return error;
}