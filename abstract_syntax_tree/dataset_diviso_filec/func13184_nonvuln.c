void RGWGetObjTags_ObjStore_S3::send_response_data(bufferlist& bl)
{
  dump_errno(s);
  end_header(s, this, "STR");
  dump_start(s);

  s->formatter->open_object_section_in_ns("STR", XMLNS_AWS_S3);
  s->formatter->open_object_section("STR");
  if (has_tags){
    RGWObjTagSet_S3 tagset;
    bufferlist::iterator iter = bl.begin();
    try {
      tagset.decode(iter);
    } catch (buffer::error& err) {
      ldout(s->cct,0) << "STR" << dendl;
      op_ret= -EIO;
      return;
    }
    tagset.dump_xml(s->formatter);
  }
  s->formatter->close_section();
  s->formatter->close_section();
  rgw_flush_formatter_and_reset(s, s->formatter);
}