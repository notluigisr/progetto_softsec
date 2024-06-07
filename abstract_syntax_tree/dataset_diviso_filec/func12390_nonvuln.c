QPDFWriter::writeHeader()
{
    setMinimumPDFVersion(this->m->pdf.getPDFVersion(),
                         this->m->pdf.getExtensionLevel());
    this->m->final_pdf_version = this->m->min_pdf_version;
    this->m->final_extension_level = this->m->min_extension_level;
    if (! this->m->forced_pdf_version.empty())
    {
	QTC::TC("STR");
	this->m->final_pdf_version = this->m->forced_pdf_version;
        this->m->final_extension_level = this->m->forced_extension_level;
    }

    writeString("STR");
    writeString(this->m->final_pdf_version);
    if (this->m->pclm)
    {
        
        writeString("STR");
    }
    else
    {
        
        
        writeString("STR");
    }
    writeStringQDF("STR");

    
    
    
    
    
}