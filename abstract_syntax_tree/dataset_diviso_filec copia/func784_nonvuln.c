static int measure_breadcrumb_dw(struct intel_context *ce)
{
	struct intel_engine_cs *engine = ce->engine;
	struct measure_breadcrumb *frame;
	int dw;

	GEM_BUG_ON(!engine->gt->scratch);

	frame = kzalloc(sizeof(*frame), GFP_KERNEL);
	if (!frame)
		return -ENOMEM;

	frame->rq.engine = engine;
	frame->rq.context = ce;
	rcu_assign_pointer(frame->rq.timeline, ce->timeline);

	frame->ring.vaddr = frame->cs;
	frame->ring.size = sizeof(frame->cs);
	frame->ring.wrap =
		BITS_PER_TYPE(frame->ring.size) - ilog2(frame->ring.size);
	frame->ring.effective_size = frame->ring.size;
	intel_ring_update_space(&frame->ring);
	frame->rq.ring = &frame->ring;

	mutex_lock(&ce->timeline->mutex);
	spin_lock_irq(&engine->active.lock);

	dw = engine->emit_fini_breadcrumb(&frame->rq, frame->cs) - frame->cs;

	spin_unlock_irq(&engine->active.lock);
	mutex_unlock(&ce->timeline->mutex);

	GEM_BUG_ON(dw & 1); 

	kfree(frame);
	return dw;
}