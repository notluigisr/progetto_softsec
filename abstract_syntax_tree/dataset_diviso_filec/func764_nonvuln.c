png_set_compression_strategy(png_structrp png_ptr, int strategy)
{
   png_debug(1, "STR");

   if (png_ptr == NULL)
      return;

   
   png_ptr->flags |= PNG_FLAG_ZLIB_CUSTOM_STRATEGY;
   png_ptr->zlib_strategy = strategy;
}