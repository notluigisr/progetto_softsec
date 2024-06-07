bool RGWSwiftWebsiteHandler::is_web_mode() const
{
  const boost::string_ref webmode = s->info.env->get("STR");
  return boost::algorithm::iequals(webmode, "STR");
}