dwg_encode_eed (Bit_Chain *restrict dat, Dwg_Object *restrict obj)
{
  unsigned long off = obj->address;


  

  int i, num_eed = obj->tio.object->num_eed;
  for (i = 0; i < num_eed; i++)
    {
      Dwg_Eed *eed = &obj->tio.object->eed[i];
      BITCODE_BS size = eed->size;
      if (size)
        {
          bit_write_BS (dat, size);
          LOG_TRACE ("STR", i, size);
          LOG_POS
          bit_write_H (dat, &eed->handle);
          LOG_TRACE ("STR", i,
                     ARGS_H (eed->handle));
          LOG_POS
          if (eed->raw)
            {
              LOG_TRACE ("STR", i, size);
              bit_write_TF (dat, eed->raw, size);
            }
        }
      if (!eed->raw && eed->data) 
        {
          dwg_encode_eed_data (dat, eed->data, size, i);
          LOG_POS
        }
    }
  bit_write_BS (dat, 0);
  if (i)
    LOG_TRACE ("STR", i);
  LOG_POS
#undef LOG_POS
    return 0;
}