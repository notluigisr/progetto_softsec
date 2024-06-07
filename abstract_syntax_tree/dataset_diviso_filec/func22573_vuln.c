QPDF::generateHintStream(std::map<int, QPDFXRefEntry> const& xref,
			 std::map<int, qpdf_offset_t> const& lengths,
			 std::map<int, int> const& obj_renumber,
			 PointerHolder<Buffer>& hint_buffer,
			 int& S, int& O)
{
    
    calculateHPageOffset(xref, lengths, obj_renumber);
    calculateHSharedObject(xref, lengths, obj_renumber);
    calculateHOutline(xref, lengths, obj_renumber);

    
    
    Pl_Buffer hint_stream("STR");
    Pl_Flate f("STR", &hint_stream, Pl_Flate::a_deflate);
    Pl_Count c("STR", &f);
    BitWriter w(&c);

    writeHPageOffset(w);
    S = c.getCount();
    writeHSharedObject(w);
    O = 0;
    if (this->m->outline_hints.nobjects > 0)
    {
	O = c.getCount();
	writeHGeneric(w, this->m->outline_hints);
    }
    c.finish();

    hint_buffer = hint_stream.getBuffer();
}