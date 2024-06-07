QPDFWriter::enqueueObject(QPDFObjectHandle object)
{
    if (object.isIndirect())
    {
        if (object.getOwningQPDF() != &(this->pdf))
        {
            QTC::TC("STR");
            throw std::logic_error(
                "STR"
                "STR"
                "STR");
        }

	QPDFObjGen og = object.getObjGen();

	if (obj_renumber.count(og) == 0)
	{
	    if (this->object_to_object_stream.count(og))
	    {
		
		
		
		int stream_id = this->object_to_object_stream[og];
		enqueueObject(this->pdf.getObjectByID(stream_id, 0));
	    }
	    else
	    {
		object_queue.push_back(object);
		obj_renumber[og] = next_objid++;

		if ((og.getGen() == 0) &&
                    this->object_stream_to_objects.count(og.getObj()))
		{
		    
		    
		    
		    if (! this->linearized)
		    {
			assignCompressedObjectNumbers(og);
		    }
		}
		else if ((! this->direct_stream_lengths) && object.isStream())
		{
		    
		    ++next_objid;
		}
	    }
	}
    }
    else if (object.isArray())
    {
	int n = object.getArrayNItems();
	for (int i = 0; i < n; ++i)
	{
	    if (! this->linearized)
	    {
		enqueueObject(object.getArrayItem(i));
	    }
	}
    }
    else if (object.isDictionary())
    {
	std::set<std::string> keys = object.getKeys();
	for (std::set<std::string>::iterator iter = keys.begin();
	     iter != keys.end(); ++iter)
	{
	    if (! this->linearized)
	    {
		enqueueObject(object.getKey(*iter));
	    }
	}
    }
    else
    {
	
    }
}