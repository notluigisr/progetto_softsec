static void reset_csb_pointers(struct intel_engine_cs *engine)
{
	struct intel_engine_execlists * const execlists = &engine->execlists;
	const unsigned int reset_value = execlists->csb_size - 1;

	ring_set_paused(engine, 0);

	
	execlists->csb_head = reset_value;
	WRITE_ONCE(*execlists->csb_write, reset_value);
	wmb(); 

	invalidate_csb_entries(&execlists->csb_status[0],
			       &execlists->csb_status[reset_value]);
}