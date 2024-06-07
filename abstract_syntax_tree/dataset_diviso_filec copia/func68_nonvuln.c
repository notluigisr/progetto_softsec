dwg_dup_handleref (Dwg_Data *restrict dwg, const Dwg_Object_Ref *restrict ref)
{
  if (ref)
    return dwg_add_handleref (dwg, ref->handleref.code, ref->absolute_ref, NULL);
  else
    return dwg_add_handleref (dwg, 5, 0, NULL);
}