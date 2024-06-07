struct aff_pagebuf *af_cache_alloc(AFFILE *af,int64_t pagenum)
{
    if(af_trace) fprintf(af_trace,"STR",af,pagenum);

    
    if(af_cache_flush(af) < 0)
	return 0;

    
    for(int i=0;i<af->num_pbufs;i++){
	struct aff_pagebuf *p = &af->pbcache[i];
	if(p->pagenum_valid && p->pagenum==pagenum){
	    af->cache_hits++;
	    if(af_trace) fprintf(af_trace,"STR",pagenum);
	    p->last = cachetime++;
	    return p;
	}
    }

    af->cache_misses++;
    int slot = -1;
    
    for(int i=0;i<af->num_pbufs;i++){
	struct aff_pagebuf *p = &af->pbcache[i];
	if(p->pagenum_valid==0){
	    slot = i;
	    if(af_trace) fprintf(af_trace,"STR",slot,pagenum);
	    break;
	}
    }
    if(slot==-1){
	
	int oldest_i = 0;
	int oldest_t = af->pbcache[0].last;
	for(int i=1;i<af->num_pbufs;i++){
	    if(af->pbcache[i].last < oldest_t){
		oldest_t = af->pbcache[i].last;
		oldest_i = i;
	    }
	}
	slot = oldest_i;
	if(af_trace) fprintf(af_trace,"STR",slot,pagenum);
    }
    
    struct aff_pagebuf *p = &af->pbcache[slot];
    if(p->pagebuf==0){
	p->pagebuf = (unsigned char *)valloc(af->image_pagesize); 
	if(p->pagebuf==0){
	    
	    slot = 0;
	    if(af->pbcache[0].pagebuf==0) return 0; 

	    
	    p = &af->pbcache[0];
	}
    }
    memset(p->pagebuf,0,af->image_pagesize); 
    p->pagenum = pagenum;
    p->pagenum_valid = 1;
    p->pagebuf_valid = 0;
    p->pagebuf_dirty = 0;
    p->last = cachetime++;
    if(af_trace){
	fprintf(af_trace,"STR");
	for(int i=0;i<af->num_pbufs;i++){
	    fprintf(af_trace,"STR" I64d,af->pbcache[i].pagenum);
	}
	fprintf(af_trace,"STR");
    }
    return p;
}