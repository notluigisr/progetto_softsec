CreateStagingDirectory(
   const char *realRoot,       
   const char *apparentRoot)   
{
   char *result = NULL;
   int i;

   for (i = 0; i < 10 && result == NULL; i++) {
      char *realStagingDir = NULL;
      char *apparentStagingDir = NULL;

      
      realStagingDir = Str_SafeAsprintf(NULL, "STR", realRoot);
      if (mkdtemp(realStagingDir) != NULL) {
         char *randomPart = strrchr(realStagingDir, '/') + 1;
         VERIFY(*randomPart != '\0');

         apparentStagingDir = Unicode_Append(apparentRoot, randomPart);

         if (Posix_Symlink(realStagingDir, apparentStagingDir) == 0) {
            
            result = apparentStagingDir;
            apparentStagingDir = NULL;
         } else {
            Warning("STR", apparentStagingDir, Err_ErrString());
            Posix_Rmdir(realStagingDir);
         }
      } else {
         Warning("STR", realStagingDir, Err_ErrString());
      }

      free(realStagingDir);
      free(apparentStagingDir);
   }

   return result;
}