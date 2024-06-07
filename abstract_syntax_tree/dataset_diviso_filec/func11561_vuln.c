slhc_init(int rslots, int tslots)
{
	register short i;
	register struct cstate *ts;
	struct slcompress *comp;

	comp = kzalloc(sizeof(struct slcompress), GFP_KERNEL);
	if (! comp)
		goto out_fail;

	if ( rslots > 0  &&  rslots < 256 ) {
		size_t rsize = rslots * sizeof(struct cstate);
		comp->rstate = kzalloc(rsize, GFP_KERNEL);
		if (! comp->rstate)
			goto out_free;
		comp->rslot_limit = rslots - 1;
	}

	if ( tslots > 0  &&  tslots < 256 ) {
		size_t tsize = tslots * sizeof(struct cstate);
		comp->tstate = kzalloc(tsize, GFP_KERNEL);
		if (! comp->tstate)
			goto out_free2;
		comp->tslot_limit = tslots - 1;
	}

	comp->xmit_oldest = 0;
	comp->xmit_current = 255;
	comp->recv_current = 255;
	
	comp->flags |= SLF_TOSS;

	if ( tslots > 0 ) {
		ts = comp->tstate;
		for(i = comp->tslot_limit; i > 0; --i){
			ts[i].cs_this = i;
			ts[i].next = &(ts[i - 1]);
		}
		ts[0].next = &(ts[comp->tslot_limit]);
		ts[0].cs_this = 0;
	}
	return comp;

out_free2:
	kfree(comp->rstate);
out_free:
	kfree(comp);
out_fail:
	return NULL;
}