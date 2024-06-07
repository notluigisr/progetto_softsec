int RGWPostObj_ObjStore_S3::get_tags()
{
  string tags_str;
  if (part_str(parts, "STR", &tags_str)) {
    RGWObjTagsXMLParser parser;
    if (!parser.init()){
      ldout(s->cct, 0) << "STR" << dendl;
      err_msg = "STR";
      return -EINVAL; 
    }
    if (!parser.parse(tags_str.c_str(), tags_str.size(), 1)) {
      ldout(s->cct,0 ) << "STR" << dendl;
      err_msg = "STR";
      return -EINVAL;
    }

    RGWObjTagSet_S3 *obj_tags_s3;
    RGWObjTagging_S3 *tagging;

    tagging = static_cast<RGWObjTagging_S3 *>(parser.find_first("STR"));
    obj_tags_s3 = static_cast<RGWObjTagSet_S3 *>(tagging->find_first("STR"));
    if(!obj_tags_s3){
      return -ERR_MALFORMED_XML;
    }

    RGWObjTags obj_tags;
    int r = obj_tags_s3->rebuild(obj_tags);
    if (r < 0)
      return r;

    bufferlist tags_bl;
    obj_tags.encode(tags_bl);
    ldout(s->cct, 20) << "STR" << dendl;
    attrs[RGW_ATTR_TAGS] = tags_bl;
  }


  return 0;
}