dwg_encode_entity (Dwg_Object *restrict obj, Bit_Chain *hdl_dat, Bit_Chain *str_dat,
                   Bit_Chain *dat)
{
  int error = 0;
  Dwg_Object_Entity *ent = obj->tio.entity;
  Dwg_Object_Entity *_obj = ent;
  Dwg_Data *dwg = ent->dwg;

  if (!obj || !dat)
    return DWG_ERR_INVALIDDWG;
  PRE (R_13)
  {

    if (FIELD_VALUE (flag_r11) & 4 && FIELD_VALUE (kind_r11) > 2
        && FIELD_VALUE (kind_r11) != 22)
      FIELD_RD (elevation_r11, 30);
    if (FIELD_VALUE (flag_r11) & 8)
      FIELD_RD (thickness_r11, 39);
    if (FIELD_VALUE (flag_r11) & 0x20)
      {
        Dwg_Object_Ref *hdl
            = dwg_decode_handleref_with_code (dat, obj, dwg, 0);
        if (hdl)
          obj->handle = hdl->handleref;
      }
    if (FIELD_VALUE (extra_r11) & 4)
      FIELD_RS (paper_r11, 0);
  }

  SINCE (R_2007) { *str_dat = *dat; }
  VERSIONS (R_2000, R_2007)
  {
    obj->bitsize_pos = bit_position (dat);
    bit_write_RL (dat, obj->bitsize);
    LOG_TRACE ("STR", obj->bitsize,
               obj->bitsize_pos / 8, obj->bitsize_pos % 8);
  }
  if (obj->bitsize)
    obj->hdlpos = obj->address * 8 + obj->bitsize;
  SINCE (R_2007)
  {
    
    
    SINCE (R_2010)
    {
      if (obj->bitsize)
        {
          obj->hdlpos += 8;
          
          LOG_HANDLE ("STR", obj->hdlpos);
        }
    }
    
    error |= obj_string_stream (dat, obj, str_dat);
  }

  bit_write_H (dat, &obj->handle);
  LOG_TRACE ("STR", ARGS_H (obj->handle))
  PRE (R_13) { return DWG_ERR_NOTYETSUPPORTED; }

  error |= dwg_encode_eed (dat, obj);
  
  

  
  
  

  return error;
}