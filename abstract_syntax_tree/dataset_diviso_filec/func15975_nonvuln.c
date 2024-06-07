dwg_free_common_entity_data (Dwg_Object *obj)
{

  Dwg_Data *dwg = obj->parent;
  Bit_Chain *dat = &pdat;
  Bit_Chain *hdl_dat = &pdat;
  Dwg_Object_Entity *_obj;
  Dwg_Object_Entity *ent;
  BITCODE_BL vcount;
  int error = 0;

  ent = obj->tio.entity;
  if (!ent)
    return;
  _obj = ent;

  FREE_IF (ent->preview);

  
  
  SINCE (R_13) {
  
  }
  
}