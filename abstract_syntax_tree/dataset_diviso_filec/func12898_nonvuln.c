QPDFWriter::writeObject(QPDFObjectHandle object, int object_stream_index)
{
    QPDFObjGen old_og = object.getObjGen();

    if ((object_stream_index == -1) &&
        (old_og.getGen() == 0) &&
	(this->m->object_stream_to_objects.count(old_og.getObj())))
    {
	writeObjectStream(object);
	return;
    }

    indicateProgress(false, false);
    int new_id = this->m->obj_renumber[old_og];
    if (this->m->qdf_mode)
    {
	if (this->m->page_object_to_seq.count(old_og))
	{
	    writeString("STR");
	    writeString(
		QUtil::int_to_string(
		    this->m->page_object_to_seq[old_og]));
	    writeString("STR");
	}
	if (this->m->contents_to_page_seq.count(old_og))
	{
	    writeString("STR");
	    writeString(
		QUtil::int_to_string(
		    this->m->contents_to_page_seq[old_og]));
	    writeString("STR");
	}
    }
    if (object_stream_index == -1)
    {
	if (this->m->qdf_mode && (! this->m->suppress_original_object_ids))
	{
	    writeString("STR" +
			QUtil::int_to_string(object.getObjectID()) + "STR" +
			QUtil::int_to_string(object.getGeneration()) + "STR");
	}
	openObject(new_id);
	setDataKey(new_id);
	unparseObject(object, 0, 0);
	this->m->cur_data_key.clear();
	closeObject(new_id);
    }
    else
    {
	unparseObject(object, 0, f_in_ostream);
	writeString("STR");
    }

    if ((! this->m->direct_stream_lengths) && object.isStream())
    {
	if (this->m->qdf_mode)
	{
	    if (this->m->added_newline)
	    {
		writeString("STR");
	    }
	}
	openObject(new_id + 1);
	writeString(QUtil::uint_to_string(this->m->cur_stream_length));
	closeObject(new_id + 1);
    }
}