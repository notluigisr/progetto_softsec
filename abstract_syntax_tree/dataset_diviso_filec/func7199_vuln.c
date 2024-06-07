QPDFWriter::generateObjectStreams()
{
    
    
    
    
    
    
    

    

    std::vector<QPDFObjGen> const& eligible =
        QPDF::Writer::getCompressibleObjGens(this->m->pdf);
    unsigned int n_object_streams = (eligible.size() + 99) / 100;
    if (n_object_streams == 0)
    {
        return;
    }
    unsigned int n_per = eligible.size() / n_object_streams;
    if (n_per * n_object_streams < eligible.size())
    {
	++n_per;
    }
    unsigned int n = 0;
    int cur_ostream = 0;
    for (std::vector<QPDFObjGen>::const_iterator iter = eligible.begin();
	 iter != eligible.end(); ++iter)
    {
	if ((n % n_per) == 0)
	{
	    if (n > 0)
	    {
		QTC::TC("STR");
	    }
	    n = 0;
	}
	if (n == 0)
	{
	    
	    
	    
	    cur_ostream = this->m->pdf.makeIndirectObject(
		QPDFObjectHandle::newNull()).getObjectID();
	}
	this->m->object_to_object_stream[*iter] = cur_ostream;
	++n;
    }
}