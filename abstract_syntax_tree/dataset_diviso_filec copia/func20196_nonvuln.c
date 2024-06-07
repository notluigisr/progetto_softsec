png_set_benign_errors(png_structrp png_ptr, int allowed)
{
   png_debug(1, "STR");

   

   if (allowed != 0)
      png_ptr->flags |= PNG_FLAG_BENIGN_ERRORS_WARN |
         PNG_FLAG_APP_WARNINGS_WARN | PNG_FLAG_APP_ERRORS_WARN;

   else
      png_ptr->flags &= ~(PNG_FLAG_BENIGN_ERRORS_WARN |
         PNG_FLAG_APP_WARNINGS_WARN | PNG_FLAG_APP_ERRORS_WARN);
}