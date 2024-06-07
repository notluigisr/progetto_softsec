QPDFWriter::calculateXrefStreamPadding(int xref_bytes)
{
    
    
    
    
    
    
    

    return 16 + (5 * ((xref_bytes + 16383) / 16384));
}