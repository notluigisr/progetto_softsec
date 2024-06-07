static struct inet_frag_queue *inet_frag_intern(struct netns_frags *nf,
		struct inet_frag_queue *qp_in, struct inet_frags *f,
		void *arg)
{
	struct inet_frag_bucket *hb;
	struct inet_frag_queue *qp;
	unsigned int hash;

	read_lock(&f->lock); 
	
	hash = f->hashfn(qp_in);
	hb = &f->hash[hash];
	spin_lock(&hb->chain_lock);

#ifdef CONFIG_SMP
	
	hlist_for_each_entry(qp, &hb->chain, list) {
		if (qp->net == nf && f->match(qp, arg)) {
			atomic_inc(&qp->refcnt);
			spin_unlock(&hb->chain_lock);
			read_unlock(&f->lock);
			qp_in->last_in |= INET_FRAG_COMPLETE;
			inet_frag_put(qp_in, f);
			return qp;
		}
	}
#endif
	qp = qp_in;
	if (!mod_timer(&qp->timer, jiffies + nf->timeout))
		atomic_inc(&qp->refcnt);

	atomic_inc(&qp->refcnt);
	hlist_add_head(&qp->list, &hb->chain);
	spin_unlock(&hb->chain_lock);
	read_unlock(&f->lock);
	inet_frag_lru_add(nf, qp);
	return qp;
}