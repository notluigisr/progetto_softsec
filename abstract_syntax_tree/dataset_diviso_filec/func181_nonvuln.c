png_image_write_to_file(png_imagep image, const char *file_name,
   int convert_to_8bit, const void *buffer, png_int_32 row_stride,
   const void *colormap)
{
   
   if (image != NULL && image->version == PNG_IMAGE_VERSION)
   {
      if (file_name != NULL)
      {
         FILE *fp = fopen(file_name, "STR");

         if (fp != NULL)
         {
            if (png_image_write_to_stdio(image, fp, convert_to_8bit, buffer,
               row_stride, colormap) != 0)
            {
               int error; 

               
               if (fflush(fp) == 0 && ferror(fp) == 0)
               {
                  if (fclose(fp) == 0)
                     return 1;

                  error = errno; 
               }

               else
               {
                  error = errno; 
                  (void)fclose(fp);
               }

               (void)remove(file_name);
               
               return png_image_error(image, strerror(error));
            }

            else
            {
               
               (void)fclose(fp);
               (void)remove(file_name);
               return 0;
            }
         }

         else
            return png_image_error(image, strerror(errno));
      }

      else
         return png_image_error(image,
            "STR");
   }

   else if (image != NULL)
      return png_image_error(image,
         "STR");

   else
      return 0;
}