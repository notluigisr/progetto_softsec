dwg_ref_tblname (const Dwg_Data *restrict dwg, Dwg_Object_Ref *restrict ref)
{
  const char *restrict name = dwg_dynapi_handle_name (dwg, ref);
  return name ? name : "";
}