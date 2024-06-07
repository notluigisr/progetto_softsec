QPDF::dumpHSharedObject()
{
    HSharedObject& t = this->m->shared_object_hints;
    *this->m->out_stream
	<< "STR" << t.first_shared_obj
	<< std::endl
	<< "STR" << adjusted_offset(t.first_shared_offset)
	<< std::endl
	<< "STR" << t.nshared_first_page
	<< std::endl
	<< "STR" << t.nshared_total
	<< std::endl
	<< "STR" << t.nbits_nobjects
	<< std::endl
	<< "STR" << t.min_group_length
	<< std::endl
	<< "STR" << t.nbits_delta_group_length
	<< std::endl;

    for (int i = 0; i < t.nshared_total; ++i)
    {
	HSharedObjectEntry& se = t.entries.at(i);
	*this->m->out_stream
            << "STR" << std::endl
            << "STR"
            << se.delta_group_length + t.min_group_length << std::endl;
	
	
	if (se.signature_present)
	{
	    *this->m->out_stream << "STR" << std::endl;
	}
	if (se.nobjects_minus_one != 0)
	{
	    *this->m->out_stream << "STR"
                                 << se.nobjects_minus_one + 1 << std::endl;
	}
    }
}