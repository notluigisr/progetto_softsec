QPDF::readHSharedObject(BitStream h)
{
    HSharedObject& t = this->m->shared_object_hints;

    t.first_shared_obj = h.getBits(32);			    
    t.first_shared_offset = h.getBits(32);		    
    t.nshared_first_page = h.getBits(32);		    
    t.nshared_total = h.getBits(32);			    
    t.nbits_nobjects = h.getBits(16);			    
    t.min_group_length = h.getBits(32);			    
    t.nbits_delta_group_length = h.getBits(16);		    

    QTC::TC("STR",
	    (t.nshared_total > t.nshared_first_page) ? 1 : 0);

    std::vector<HSharedObjectEntry>& entries = t.entries;
    entries.clear();
    int nitems = t.nshared_total;
    load_vector_int(h, nitems, entries,
		    t.nbits_delta_group_length,
		    &HSharedObjectEntry::delta_group_length);
    load_vector_int(h, nitems, entries,
		    1, &HSharedObjectEntry::signature_present);
    for (int i = 0; i < nitems; ++i)
    {
	if (entries.at(i).signature_present)
	{
	    
	    
	    
	    for (int j = 0; j < 4; ++j)
	    {
		(void) h.getBits(32);
	    }
	}
    }
    load_vector_int(h, nitems, entries,
		    t.nbits_nobjects,
		    &HSharedObjectEntry::nobjects_minus_one);
}