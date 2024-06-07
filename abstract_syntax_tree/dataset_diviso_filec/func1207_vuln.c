QPDF::adjusted_offset(int offset)
{
    
    
    
    if (offset >= this->m->linp.H_offset)
    {
	return offset + this->m->linp.H_length;
    }
    return offset;
}