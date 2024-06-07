void RGWGetBucketPolicyStatus_ObjStore_S3::send_response()
{
  if (op_ret) {
    set_req_state_err(s, op_ret);
  }
  dump_errno(s);
  end_header(s, this, "STR");
  dump_start(s);

  s->formatter->open_object_section_in_ns("STR", XMLNS_AWS_S3);
  
  
  
  
  s->formatter->dump_bool("STR", isPublic);
  s->formatter->close_section();
  rgw_flush_formatter_and_reset(s, s->formatter);

}