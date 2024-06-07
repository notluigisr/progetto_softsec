QPDF::readHPageOffset(BitStream h)
{
    
    

    HPageOffset& t = this->m->page_offset_hints;

    t.min_nobjects = h.getBits(32);		  	    
    t.first_page_offset = h.getBits(32);		    
    t.nbits_delta_nobjects = h.getBits(16);		    
    t.min_page_length = h.getBits(32);			    
    t.nbits_delta_page_length = h.getBits(16);		    
    t.min_content_offset = h.getBits(32);		    
    t.nbits_delta_content_offset = h.getBits(16);	    
    t.min_content_length = h.getBits(32);		    
    t.nbits_delta_content_length = h.getBits(16);	    
    t.nbits_nshared_objects = h.getBits(16);		    
    t.nbits_shared_identifier = h.getBits(16);		    
    t.nbits_shared_numerator = h.getBits(16);		    
    t.shared_denominator = h.getBits(16);		    

    std::vector<HPageOffsetEntry>& entries = t.entries;
    entries.clear();
    unsigned int nitems = this->m->linp.npages;
    load_vector_int(h, nitems, entries,
		    t.nbits_delta_nobjects,
		    &HPageOffsetEntry::delta_nobjects);
    load_vector_int(h, nitems, entries,
		    t.nbits_delta_page_length,
		    &HPageOffsetEntry::delta_page_length);
    load_vector_int(h, nitems, entries,
		    t.nbits_nshared_objects,
		    &HPageOffsetEntry::nshared_objects);
    load_vector_vector(h, nitems, entries,
		       &HPageOffsetEntry::nshared_objects,
		       t.nbits_shared_identifier,
		       &HPageOffsetEntry::shared_identifiers);
    load_vector_vector(h, nitems, entries,
		       &HPageOffsetEntry::nshared_objects,
		       t.nbits_shared_numerator,
		       &HPageOffsetEntry::shared_numerators);
    load_vector_int(h, nitems, entries,
		    t.nbits_delta_content_offset,
		    &HPageOffsetEntry::delta_content_offset);
    load_vector_int(h, nitems, entries,
		    t.nbits_delta_content_length,
		    &HPageOffsetEntry::delta_content_length);
}