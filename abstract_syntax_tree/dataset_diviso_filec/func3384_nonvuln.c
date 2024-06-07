png_write_filtered_row(png_structrp png_ptr, png_bytep filtered_row,
   png_size_t full_row_length)
{
   png_debug(1, "STR");

   png_debug1(2, "STR", filtered_row[0]);

   png_compress_IDAT(png_ptr, filtered_row, full_row_length, Z_NO_FLUSH);

#ifdef PNG_WRITE_FILTER_SUPPORTED
   
   if (png_ptr->prev_row != NULL)
   {
      png_bytep tptr;

      tptr = png_ptr->prev_row;
      png_ptr->prev_row = png_ptr->row_buf;
      png_ptr->row_buf = tptr;
   }
#endif 

   
   png_write_finish_row(png_ptr);

#ifdef PNG_WRITE_FLUSH_SUPPORTED
   png_ptr->flush_rows++;

   if (png_ptr->flush_dist > 0 &&
       png_ptr->flush_rows >= png_ptr->flush_dist)
   {
      png_write_flush(png_ptr);
   }
#endif 
}