QPDF::readHintStream(Pipeline& pl, qpdf_offset_t offset, size_t length)
{
    int obj;
    int gen;
    QPDFObjectHandle H = readObjectAtOffset(
	false, offset, "STR", -1, 0, obj, gen);
    ObjCache& oc = this->m->obj_cache[QPDFObjGen(obj, gen)];
    qpdf_offset_t min_end_offset = oc.end_before_space;
    qpdf_offset_t max_end_offset = oc.end_after_space;
    if (! H.isStream())
    {
	throw QPDFExc(qpdf_e_damaged_pdf, this->m->file->getName(),
		      "STR",
		      this->m->file->getLastOffset(),
		      "STR");
    }

    QPDFObjectHandle Hdict = H.getDict();

    
    
    
    
    
    QPDFObjectHandle length_obj = Hdict.getKey("STR");
    if (length_obj.isIndirect())
    {
	QTC::TC("STR");
	
	(void) length_obj.getIntValue();
	ObjCache& oc = this->m->obj_cache[length_obj.getObjGen()];
	min_end_offset = oc.end_before_space;
	max_end_offset = oc.end_after_space;
    }
    else
    {
	QTC::TC("STR");
    }
    qpdf_offset_t computed_end = offset + length;
    if ((computed_end < min_end_offset) ||
	(computed_end > max_end_offset))
    {
	*this->m->out_stream << "STR" << computed_end
                             << "STR"
                             << max_end_offset << std::endl;
	throw QPDFExc(qpdf_e_damaged_pdf, this->m->file->getName(),
		      "STR",
		      this->m->file->getLastOffset(),
		      "STR");
    }
    H.pipeStreamData(&pl, 0, qpdf_dl_specialized);
    return Hdict;
}