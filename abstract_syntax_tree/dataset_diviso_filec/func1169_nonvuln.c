void OSD::dispatch_context_transaction(PG::RecoveryCtx &ctx, PG *pg,
                                       ThreadPool::TPHandle *handle)
{
  if (!ctx.transaction->empty()) {
    if (!ctx.created_pgs.empty()) {
      ctx.on_applied->add(new C_OpenPGs(ctx.created_pgs, store, this));
    }
    int tr = store->queue_transaction(
      pg->osr.get(),
      std::move(*ctx.transaction), ctx.on_applied, ctx.on_safe, NULL,
      TrackedOpRef(), handle);
    delete (ctx.transaction);
    assert(tr == 0);
    ctx.transaction = new ObjectStore::Transaction;
    ctx.on_applied = new C_Contexts(cct);
    ctx.on_safe = new C_Contexts(cct);
  }
}