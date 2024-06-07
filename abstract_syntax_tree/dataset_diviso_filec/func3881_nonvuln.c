void RGWDeleteBucketWebsite::execute()
{
  op_ret = retry_raced_bucket_write(store, s, [this] {
      s->bucket_info.has_website = false;
      s->bucket_info.website_conf = RGWBucketWebsiteConf();
      op_ret = store->put_bucket_instance_info(s->bucket_info, false,
					       real_time(), &s->bucket_attrs);
      return op_ret;
    });
  if (op_ret < 0) {
    ldout(s->cct, 0) << "STR" << op_ret << dendl;
    return;
  }
}