png_handle_as_unknown(png_const_structrp png_ptr, png_const_bytep chunk_name)
{
   
   png_const_bytep p, p_end;

   if (png_ptr == NULL || chunk_name == NULL || png_ptr->num_chunk_list == 0)
      return PNG_HANDLE_CHUNK_AS_DEFAULT;

   p_end = png_ptr->chunk_list;
   p = p_end + png_ptr->num_chunk_list*5; 

   
   do 
   {
      p -= 5;

      if (memcmp(chunk_name, p, 4) == 0)
         return p[4];
   }
   while (p > p_end);

   
   return PNG_HANDLE_CHUNK_AS_DEFAULT;
}