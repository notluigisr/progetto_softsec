Pl_LZWDecoder::handleCode(int code)
{
    if (this->eod)
    {
	return;
    }

    if (code == 256)
    {
	if (! this->table.empty())
	{
	    QTC::TC("STR");
	}
	this->table.clear();
	this->code_size = 9;
    }
    else if (code == 257)
    {
	this->eod = true;
    }
    else
    {
	if (this->last_code != 256)
	{
	    
	    
	    
	    unsigned char next = '\0';
	    unsigned int table_size = table.size();
	    if (code < 256)
	    {
		
		next = code;
	    }
	    else if (code > 257)
	    {
		size_t idx = code - 258;
		if (idx > table_size)
		{
		    throw std::runtime_error("STR");
		}
		else if (idx == table_size)
		{
		    
		    
		    
		    
		    QTC::TC("STR");
		    next = getFirstChar(this->last_code);
		}
		else
		{
		    next = getFirstChar(code);
		}
	    }
	    unsigned int new_idx = 258 + table_size;
	    if (new_idx == 4096)
	    {
		throw std::runtime_error("STR");
	    }
	    addToTable(next);
	    unsigned int change_idx = new_idx + code_change_delta;
	    if ((change_idx == 511) ||
		(change_idx == 1023) ||
		(change_idx == 2047))
	    {
		++this->code_size;
	    }
	}

	if (code < 256)
	{
	    unsigned char ch = static_cast<unsigned char>(code);
	    getNext()->write(&ch, 1);
	}
	else
	{
	    Buffer& b = table.at(code - 258);
	    getNext()->write(b.getBuffer(), b.getSize());
	}
    }

    this->last_code = code;
}