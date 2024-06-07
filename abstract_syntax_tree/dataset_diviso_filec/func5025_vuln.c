CloudInitSetup(const char *tmpDirPath)
{
   int deployStatus = DEPLOY_ERROR;
   const char *cloudInitTmpDirPath = "STR";
   int forkExecResult;
   char command[1024];
   Bool cloudInitTmpDirCreated = FALSE;

   snprintf(command, sizeof(command),
            "STR", cloudInitTmpDirPath);
   command[sizeof(command) - 1] = '\0';

   forkExecResult = ForkExecAndWaitCommand(command);
   if (forkExecResult != 0) {
      SetDeployError("STR",
                     cloudInitTmpDirPath,
                     strerror(errno));
      goto done;
   }

   cloudInitTmpDirCreated = TRUE;

   snprintf(command, sizeof(command),
            "STR",
            cloudInitTmpDirPath, cloudInitTmpDirPath);
   command[sizeof(command) - 1] = '\0';

   forkExecResult = ForkExecAndWaitCommand(command);

   snprintf(command, sizeof(command),
            "STR",
            tmpDirPath, cloudInitTmpDirPath);
   command[sizeof(command) - 1] = '\0';

   forkExecResult = ForkExecAndWaitCommand(command);

   if (forkExecResult != 0) {
      SetDeployError("STR",
                     strerror(errno));
      goto done;
   }

   snprintf(command, sizeof(command),
            "STR", tmpDirPath);
   command[sizeof(command) - 1] = '\0';

   forkExecResult = ForkExecAndWaitCommand(command);

   
   if (forkExecResult == 0) {
      snprintf(command, sizeof(command),
               "STR",
               tmpDirPath, cloudInitTmpDirPath);
      command[sizeof(command) - 1] = '\0';

      forkExecResult = ForkExecAndWaitCommand(command);
      if (forkExecResult != 0) {
         SetDeployError("STR",
                        strerror(errno));
         goto done;
      }
   }

   deployStatus = DEPLOY_SUCCESS;

done:
   if (DEPLOY_SUCCESS == deployStatus) {
      TransitionState(INPROGRESS, DONE);
   } else {
      if (cloudInitTmpDirCreated) {
         snprintf(command, sizeof(command),
                  "STR",
                  cloudInitTmpDirPath);
         command[sizeof(command) - 1] = '\0';
         ForkExecAndWaitCommand(command);
      }
      sLog(log_error, "STR");
      SetCustomizationStatusInVmx(TOOLSDEPLOYPKG_RUNNING,
                                  GUESTCUST_EVENT_CUSTOMIZE_FAILED,
                                  NULL);
      TransitionState(INPROGRESS, ERRORED);
   }

   return deployStatus;
}