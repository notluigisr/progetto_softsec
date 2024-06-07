QPDF::writeHPageOffset(BitWriter& w)
{
    HPageOffset& t = this->m->page_offset_hints;

    w.writeBits(t.min_nobjects, 32);			    
    w.writeBits(t.first_page_offset, 32);		    
    w.writeBits(t.nbits_delta_nobjects, 16);		    
    w.writeBits(t.min_page_length, 32);			    
    w.writeBits(t.nbits_delta_page_length, 16);		    
    w.writeBits(t.min_content_offset, 32);		    
    w.writeBits(t.nbits_delta_content_offset, 16);	    
    w.writeBits(t.min_content_length, 32);		    
    w.writeBits(t.nbits_delta_content_length, 16);	    
    w.writeBits(t.nbits_nshared_objects, 16);		    
    w.writeBits(t.nbits_shared_identifier, 16);		    
    w.writeBits(t.nbits_shared_numerator, 16);		    
    w.writeBits(t.shared_denominator, 16);		    

    unsigned int nitems = getAllPages().size();
    std::vector<HPageOffsetEntry>& entries = t.entries;

    write_vector_int(w, nitems, entries,
		     t.nbits_delta_nobjects,
		     &HPageOffsetEntry::delta_nobjects);
    write_vector_int(w, nitems, entries,
		     t.nbits_delta_page_length,
		     &HPageOffsetEntry::delta_page_length);
    write_vector_int(w, nitems, entries,
		     t.nbits_nshared_objects,
		     &HPageOffsetEntry::nshared_objects);
    write_vector_vector(w, nitems, entries,
			&HPageOffsetEntry::nshared_objects,
			t.nbits_shared_identifier,
			&HPageOffsetEntry::shared_identifiers);
    write_vector_vector(w, nitems, entries,
			&HPageOffsetEntry::nshared_objects,
			t.nbits_shared_numerator,
			&HPageOffsetEntry::shared_numerators);
    write_vector_int(w, nitems, entries,
		     t.nbits_delta_content_offset,
		     &HPageOffsetEntry::delta_content_offset);
    write_vector_int(w, nitems, entries,
		     t.nbits_delta_content_length,
		     &HPageOffsetEntry::delta_content_length);
}