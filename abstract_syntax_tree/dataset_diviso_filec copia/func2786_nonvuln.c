png_set_flush(png_structrp png_ptr, int nrows)
{
   png_debug(1, "STR");

   if (png_ptr == NULL)
      return;

   png_ptr->flush_dist = (nrows < 0 ? 0 : nrows);
}