QPDF_Stream::QPDF_Stream(QPDF* qpdf, int objid, int generation,
			 QPDFObjectHandle stream_dict,
			 qpdf_offset_t offset, size_t length) :
    qpdf(qpdf),
    objid(objid),
    generation(generation),
    stream_dict(stream_dict),
    offset(offset),
    length(length)
{
    if (! stream_dict.isDictionary())
    {
	throw std::logic_error(
	    "STR"
	    "STR");
    }
    setStreamDescription();
}