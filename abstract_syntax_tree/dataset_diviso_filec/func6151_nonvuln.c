QPDF::insertXrefEntry(int obj, int f0, qpdf_offset_t f1, int f2, bool overwrite)
{
    
    
    
    
    
    
    

    
    
    
    { 
	int gen = (f0 == 2 ? 0 : f2);
	QPDFObjGen og(obj, gen);
	if (this->xref_table.count(og))
	{
	    if (overwrite)
	    {
		QTC::TC("STR");
		this->xref_table.erase(og);
	    }
	    else
	    {
		QTC::TC("STR");
		return;
	    }
	}
	if (this->deleted_objects.count(obj))
	{
	    QTC::TC("STR");
	    return;
	}
    }

    switch (f0)
    {
      case 0:
	this->deleted_objects.insert(obj);
	break;

      case 1:
	
	QTC::TC("STR", ((f2 > 0) ? 1 : 0));
	this->xref_table[QPDFObjGen(obj, f2)] = QPDFXRefEntry(f0, f1, f2);
	break;

      case 2:
	this->xref_table[QPDFObjGen(obj, 0)] = QPDFXRefEntry(f0, f1, f2);
	break;

      default:
	throw QPDFExc(qpdf_e_damaged_pdf, this->file->getName(),
		      "STR", this->file->getLastOffset(),
		      "STR" +
		      QUtil::int_to_string(f0));
	break;
    }
}