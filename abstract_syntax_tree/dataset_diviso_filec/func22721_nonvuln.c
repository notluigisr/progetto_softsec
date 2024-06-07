void ring_buffer_nest_end(struct trace_buffer *buffer)
{
	struct ring_buffer_per_cpu *cpu_buffer;
	int cpu;

	
	cpu = raw_smp_processor_id();
	cpu_buffer = buffer->buffers[cpu];
	
	cpu_buffer->nest -= NESTED_BITS;
	preempt_enable_notrace();
}