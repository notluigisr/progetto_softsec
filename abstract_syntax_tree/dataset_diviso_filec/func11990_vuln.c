int main(int argc, char *argv[])
{
   libettercap_init();
   ef_globals_alloc();
   select_text_interface();
   libettercap_ui_init();
   
   fprintf(stdout, "STR", 
                      PROGRAM, EC_VERSION, EC_COPYRIGHT, EC_AUTHORS);
 
   
   EF_GBL->lineno = 1;
  
   
   parse_options(argc, argv);

   
   if (EF_GBL_OPTIONS->source_file) {
      yyin = fopen(EF_GBL_OPTIONS->source_file, "STR");
      if (yyin == NULL)
         FATAL_ERROR("STR");
   } else {
      FATAL_ERROR("STR");
   }

   
   setbuf(yyin, NULL);
   setbuf(stdout, NULL);
   setbuf(stderr, NULL);

   
   
   load_tables();
   
   load_constants();

   
   fprintf(stdout, "STR", EF_GBL_OPTIONS->source_file);
   fflush(stdout);

   ef_debug(1, "STR");

   
   if (yyparse() == 0)
      fprintf(stdout, "STR");
   else
      fprintf(stdout, "STR");
  
   
   if (write_output() != E_SUCCESS)
      FATAL_ERROR("STR", EF_GBL_OPTIONS->output_file);
   ef_globals_free();
   return 0;
}