void RGWListBucket_ObjStore_S3::send_versioned_response()
{
  s->formatter->open_object_section_in_ns("STR", XMLNS_AWS_S3);
  if (strcasecmp(encoding_type.c_str(), "STR") == 0) {
    s->formatter->dump_string("STR");
    encode_key = true;
  }
  RGWListBucket_ObjStore_S3::send_common_versioned_response();
  s->formatter->dump_string("STR", marker.name);
  s->formatter->dump_string("STR", marker.instance);
  if (is_truncated && !next_marker.empty()) {
    s->formatter->dump_string("STR", next_marker.name);
    if (next_marker.instance.empty()) {
      s->formatter->dump_string("STR");  
    }
    else {
      s->formatter->dump_string("STR", next_marker.instance);
    }
  }

  if (op_ret >= 0) {
    if (objs_container) {
      s->formatter->open_array_section("STR");
    }
 
    vector<rgw_bucket_dir_entry>::iterator iter;
    for (iter = objs.begin(); iter != objs.end(); ++iter) {
      const char *section_name = (iter->is_delete_marker() ? "STR"
          : "STR");
      s->formatter->open_object_section(section_name);
      if (objs_container) {
        s->formatter->dump_bool("STR", iter->is_delete_marker());
      }
      rgw_obj_key key(iter->key);
      if (encode_key) {
        string key_name;
        url_encode(key.name, key_name);
        s->formatter->dump_string("STR", key_name);
      } 
      else {
        s->formatter->dump_string("STR", key.name);
      }
      string version_id = key.instance;
      if (version_id.empty()) {
        version_id = "STR";
      }
      if (s->system_request) {
        if (iter->versioned_epoch > 0) {
          s->formatter->dump_int("STR", iter->versioned_epoch);
        }
        s->formatter->dump_string("STR", iter->tag);
        utime_t ut(iter->meta.mtime);
        ut.gmtime_nsec(s->formatter->dump_stream("STR"));
      }
      s->formatter->dump_string("STR", version_id);
      s->formatter->dump_bool("STR", iter->is_current());
      dump_time(s, "STR", &iter->meta.mtime);
      if (!iter->is_delete_marker()) {
        s->formatter->dump_format("STR", iter->meta.etag.c_str());
        s->formatter->dump_int("STR", iter->meta.accounted_size);
        auto& storage_class = rgw_placement_rule::get_canonical_storage_class(iter->meta.storage_class);
        s->formatter->dump_string("STR", storage_class.c_str());
      }
      dump_owner(s, iter->meta.owner, iter->meta.owner_display_name);
      if (iter->meta.appendable) {
        s->formatter->dump_string("STR");
      } else {
        s->formatter->dump_string("STR");
      }
      s->formatter->close_section(); 
    }
    if (objs_container) {
      s->formatter->close_section(); 
    }
    s->formatter->close_section(); 
  }
  rgw_flush_formatter_and_reset(s, s->formatter);
}