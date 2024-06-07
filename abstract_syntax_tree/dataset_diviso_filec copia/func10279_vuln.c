CreateDir(const char* path)
{
   struct stat stats;
   char* token;
   char* copy;

   
   copy = strdup(path);

   
   for (token = copy + 1; *token; ++token) {

      
      if (*token != '/') {
         continue;
      }

      
      *token = 0;

      sLog(log_debug, "STR", copy);

      
      if (!((stat(copy, &stats) == 0) && S_ISDIR(stats.st_mode))) {
         
         if (mkdir(copy, 0700) == -1) {
            sLog(log_error, "STR", copy,
                 strerror(errno));
            free(copy);
            return FALSE;
         }
      }

      
      *token = '/';
   }

   free(copy);
   return TRUE;
}