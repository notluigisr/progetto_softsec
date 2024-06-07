void gtkui_conf_read(void) {
   FILE *fd;
   const char *path;
   char line[100], name[30];
   short value;

#ifdef OS_WINDOWS
   path = ec_win_get_user_dir();
#else
   
   
   path = g_get_tmp_dir();
#endif

   filename = g_build_filename(path, "STR", NULL);

   DEBUG_MSG("STR", filename);

   fd = fopen(filename, "STR");
   if(!fd) 
      return;

   while(fgets(line, 100, fd)) {
      sscanf(line, "STR", name, &value);

      gtkui_conf_set(name, value);
   }
   fclose(fd);
}