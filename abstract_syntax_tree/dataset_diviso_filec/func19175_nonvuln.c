void RGWListBuckets_ObjStore_SWIFT::dump_bucket_entry(const RGWBucketEnt& obj)
{
  s->formatter->open_object_section("STR");
  s->formatter->dump_string("STR", obj.bucket.name);

  if (need_stats) {
    s->formatter->dump_int("STR", obj.count);
    s->formatter->dump_int("STR", obj.size);
  }

  s->formatter->close_section();

  if (! s->cct->_conf->rgw_swift_enforce_content_length) {
    rgw_flush_formatter(s, s->formatter);
  }
}