write_unknown_chunks(png_structrp png_ptr, png_const_inforp info_ptr,
   unsigned int where)
{
   if (info_ptr->unknown_chunks_num != 0)
   {
      png_const_unknown_chunkp up;

      png_debug(5, "STR");

      for (up = info_ptr->unknown_chunks;
           up < info_ptr->unknown_chunks + info_ptr->unknown_chunks_num;
           ++up)
         if ((up->location & where) != 0)
      {
         
#ifdef PNG_SET_UNKNOWN_CHUNKS_SUPPORTED
         int keep = png_handle_as_unknown(png_ptr, up->name);

         
         if (keep != PNG_HANDLE_CHUNK_NEVER &&
             ((up->name[3] & 0x20)  ||
              keep == PNG_HANDLE_CHUNK_ALWAYS ||
              (keep == PNG_HANDLE_CHUNK_AS_DEFAULT &&
               png_ptr->unknown_default == PNG_HANDLE_CHUNK_ALWAYS)))
#endif
         {
            
            if (up->size == 0)
               png_warning(png_ptr, "STR");

            png_write_chunk(png_ptr, up->name, up->data, up->size);
         }
      }
   }
}