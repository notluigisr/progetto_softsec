png_handle_tRNS(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
   png_byte readbuf[PNG_MAX_PALETTE_LENGTH];

   png_debug(1, "STR");

   if ((png_ptr->mode & PNG_HAVE_IHDR) == 0)
      png_chunk_error(png_ptr, "STR");

   else if ((png_ptr->mode & PNG_HAVE_IDAT) != 0)
   {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "STR");
      return;
   }

   else if (info_ptr != NULL && (info_ptr->valid & PNG_INFO_tRNS) != 0)
   {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "STR");
      return;
   }

   if (png_ptr->color_type == PNG_COLOR_TYPE_GRAY)
   {
      png_byte buf[2];

      if (length != 2)
      {
         png_crc_finish(png_ptr, length);
         png_chunk_benign_error(png_ptr, "STR");
         return;
      }

      png_crc_read(png_ptr, buf, 2);
      png_ptr->num_trans = 1;
      png_ptr->trans_color.gray = png_get_uint_16(buf);
   }

   else if (png_ptr->color_type == PNG_COLOR_TYPE_RGB)
   {
      png_byte buf[6];

      if (length != 6)
      {
         png_crc_finish(png_ptr, length);
         png_chunk_benign_error(png_ptr, "STR");
         return;
      }

      png_crc_read(png_ptr, buf, length);
      png_ptr->num_trans = 1;
      png_ptr->trans_color.red = png_get_uint_16(buf);
      png_ptr->trans_color.green = png_get_uint_16(buf + 2);
      png_ptr->trans_color.blue = png_get_uint_16(buf + 4);
   }

   else if (png_ptr->color_type == PNG_COLOR_TYPE_PALETTE)
   {
      if ((png_ptr->mode & PNG_HAVE_PLTE) == 0)
      {
         
         png_crc_finish(png_ptr, length);
         png_chunk_benign_error(png_ptr, "STR");
         return;
      }

      if (length > (unsigned int) png_ptr->num_palette ||
         length > (unsigned int) PNG_MAX_PALETTE_LENGTH ||
         length == 0)
      {
         png_crc_finish(png_ptr, length);
         png_chunk_benign_error(png_ptr, "STR");
         return;
      }

      png_crc_read(png_ptr, readbuf, length);
      png_ptr->num_trans = (png_uint_16)length;
   }

   else
   {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "STR");
      return;
   }

   if (png_crc_finish(png_ptr, 0) != 0)
   {
      png_ptr->num_trans = 0;
      return;
   }

   
   png_set_tRNS(png_ptr, info_ptr, readbuf, png_ptr->num_trans,
       &(png_ptr->trans_color));
}