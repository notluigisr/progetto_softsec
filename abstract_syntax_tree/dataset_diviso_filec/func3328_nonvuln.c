dwg_ref_object (const Dwg_Data *restrict dwg, Dwg_Object_Ref *restrict ref)
{
  if (!ref)
    return NULL;
  if (ref->obj && !dwg->dirty_refs)
    return ref->obj;
  
  
  if ((ref->handleref.code < 6
       && dwg_resolve_handleref (ref, NULL))
      || ref->absolute_ref)
    {
      Dwg_Object *obj;
      loglevel = dwg->opts & DWG_OPTS_LOGLEVEL;
      obj = dwg_resolve_handle (dwg, ref->absolute_ref);
      if (!dwg->dirty_refs && obj)
        ref->obj = obj;
      return obj;
    }
  else
    return NULL;
}