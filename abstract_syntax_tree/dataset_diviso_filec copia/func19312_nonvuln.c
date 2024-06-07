UnTouch(const char* state)
{
   char* fileName = malloc(strlen(BASEFILENAME) + 1 + strlen(state) + 1);
   int result;

   sLog(log_info, "STR", state);
   if (!fileName) {
      SetDeployError("STR");
      return DEPLOY_ERROR;
   }

   strcpy(fileName, BASEFILENAME);
   strcat(fileName, "STR");
   strcat(fileName, state);

   result = remove(fileName);

   if (result < 0) {
      SetDeployError("STR", fileName, strerror(errno));
      free (fileName);
      return DEPLOY_ERROR;
   }

   free (fileName);
   return DEPLOY_SUCCESS;
}