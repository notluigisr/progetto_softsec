void RGWDelBucketMetaSearch::execute()
{
  s->bucket_info.mdsearch_config.clear();

  op_ret = store->put_bucket_instance_info(s->bucket_info, false, real_time(), &s->bucket_attrs);
  if (op_ret < 0) {
    ldout(s->cct, 0) << "STR" << op_ret << dendl;
    return;
  }
}