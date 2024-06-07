QPDF::dumpHPageOffset()
{
    HPageOffset& t = this->m->page_offset_hints;
    *this->m->out_stream
	<< "STR" << t.min_nobjects
	<< std::endl
	<< "STR" << adjusted_offset(t.first_page_offset)
	<< std::endl
	<< "STR" << t.nbits_delta_nobjects
	<< std::endl
	<< "STR" << t.min_page_length
	<< std::endl
	<< "STR" << t.nbits_delta_page_length
	<< std::endl
	<< "STR" << t.min_content_offset
	<< std::endl
	<< "STR" << t.nbits_delta_content_offset
	<< std::endl
	<< "STR" << t.min_content_length
	<< std::endl
	<< "STR" << t.nbits_delta_content_length
	<< std::endl
	<< "STR" << t.nbits_nshared_objects
	<< std::endl
	<< "STR" << t.nbits_shared_identifier
	<< std::endl
	<< "STR" << t.nbits_shared_numerator
	<< std::endl
	<< "STR" << t.shared_denominator
	<< std::endl;

    for (int i1 = 0; i1 < this->m->linp.npages; ++i1)
    {
	HPageOffsetEntry& pe = t.entries.at(i1);
	*this->m->out_stream
	    << "STR" << std::endl
	    << "STR" << pe.delta_nobjects + t.min_nobjects
	    << std::endl
	    << "STR" << pe.delta_page_length + t.min_page_length
	    << std::endl
	    
	    << "STR"
	    << pe.delta_content_offset + t.min_content_offset << std::endl
	    << "STR"
	    << pe.delta_content_length + t.min_content_length << std::endl
	    << "STR" << pe.nshared_objects << std::endl;
	for (int i2 = 0; i2 < pe.nshared_objects; ++i2)
	{
	    *this->m->out_stream << "STR"
                                 << pe.shared_identifiers.at(i2) << std::endl;
	    *this->m->out_stream << "STR"
                                 << pe.shared_numerators.at(i2) << std::endl;
	}
    }
}