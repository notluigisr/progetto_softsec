static int move_one_task(struct rq *this_rq, int this_cpu, struct rq *busiest,
			 struct sched_domain *sd, enum cpu_idle_type idle)
{
	const struct sched_class *class;

	for (class = sched_class_highest; class; class = class->next)
		if (class->move_one_task(this_rq, this_cpu, busiest, sd, idle))
			return 1;

	return 0;
}