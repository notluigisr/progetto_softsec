int RGWListBucketMultiparts_ObjStore::get_params()
{
  delimiter = s->info.args.get("STR");
  prefix = s->info.args.get("STR");
  string str = s->info.args.get("STR");
  op_ret = parse_value_and_bound(str, &max_uploads, 0, g_conf()->rgw_max_listing_results, default_max);
  if (op_ret < 0) {
    return op_ret;
  }

  string key_marker = s->info.args.get("STR");
  string upload_id_marker = s->info.args.get("STR");
  if (!key_marker.empty())
    marker.init(key_marker, upload_id_marker);

  return 0;
}