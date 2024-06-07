QPDF::writeHSharedObject(BitWriter& w)
{
    HSharedObject& t = this->m->shared_object_hints;

    w.writeBits(t.first_shared_obj, 32);		    
    w.writeBits(t.first_shared_offset, 32);		    
    w.writeBits(t.nshared_first_page, 32);		    
    w.writeBits(t.nshared_total, 32);			    
    w.writeBits(t.nbits_nobjects, 16);			    
    w.writeBits(t.min_group_length, 32);		    
    w.writeBits(t.nbits_delta_group_length, 16);	    

    QTC::TC("STR",
	    (t.nshared_total > t.nshared_first_page) ? 1 : 0);

    int nitems = t.nshared_total;
    std::vector<HSharedObjectEntry>& entries = t.entries;

    write_vector_int(w, nitems, entries,
		     t.nbits_delta_group_length,
		     &HSharedObjectEntry::delta_group_length);
    write_vector_int(w, nitems, entries,
		     1, &HSharedObjectEntry::signature_present);
    for (int i = 0; i < nitems; ++i)
    {
	
	if (entries.at(i).signature_present != 0)
        {
            stopOnError("STR"
                        "STR");
        }
    }
    write_vector_int(w, nitems, entries,
		     t.nbits_nobjects,
		     &HSharedObjectEntry::nobjects_minus_one);
}