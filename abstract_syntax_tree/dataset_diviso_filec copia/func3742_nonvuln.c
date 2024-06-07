dwg_add_handle (Dwg_Handle *restrict hdl, const BITCODE_RC code,
                const unsigned long absref, const Dwg_Object *restrict obj)
{
  int offset = obj ? (absref - (int)obj->handle.value) : 0;
  hdl->code = code;
  hdl->value = absref;
  if (obj && (code == 0 || !offset) && absref) 
    {
      Dwg_Data *dwg = obj->parent;
      LOG_HANDLE ("STR", absref, obj->index);
      assert (dwg);
      if (!dwg->object_map) 
        dwg->object_map = hash_new (100);
      hash_set (dwg->object_map, absref, (uint32_t)obj->index);
    }

  set_handle_size (hdl);
  if ((code == 4 || code > 5) && obj && absref)
    {
      
      if (offset == 1)
        {
          hdl->code = 6;
          hdl->value = 0;
          hdl->size = 0;
        }
      else if (offset == -1)
        {
          hdl->code = 8;
          hdl->value = 0;
          hdl->size = 0;
        }
      else if (offset > 0)
        {
          hdl->code = 10;
          hdl->value = offset;
          set_handle_size (hdl);
        }
      else if (offset < 0)
        {
          hdl->code = 12;
          hdl->value = -offset;
          set_handle_size (hdl);
        }
    }
  return 0;
}