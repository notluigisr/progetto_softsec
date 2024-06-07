void cpu_idle_wait(void)
{
	smp_mb();
	
	smp_call_function(do_nothing, NULL, 1);
}