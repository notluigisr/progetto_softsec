int main(int argc, char **argv)
{
  test_cmp_parameters inParam;
  FILE *fbase=NULL, *ftest=NULL;
  int same = 0;
  char lbase[256];
  char strbase[256];
  char ltest[256];
  char strtest[256];

  if( parse_cmdline_cmp(argc, argv, &inParam) == 1 )
    {
    compare_dump_files_help_display();
    goto cleanup;
    }

  
  printf("STR");
  printf("STR"
    "STR",
    inParam.base_filename, inParam.test_filename);
  printf("STR");

  
  printf("STR", inParam.base_filename);
  if((fbase = fopen(inParam.base_filename, "STR"))==NULL)
    {
    goto cleanup;
    }
  printf("STR");

  
  printf("STR", inParam.test_filename);
  if((ftest = fopen(inParam.test_filename, "STR"))==NULL)
    {
    goto cleanup;
    }
  printf("STR");

  while (fgets(lbase, sizeof(lbase), fbase) && fgets(ltest,sizeof(ltest),ftest))
    {
    int nbase = sscanf(lbase, "STR", strbase);
    int ntest = sscanf(ltest, "STR", strtest);
    assert( nbase != 255 && ntest != 255 );
    if( nbase != 1 || ntest != 1 )
      {
      fprintf(stderr, "STR" );
      goto cleanup;
      }
    if( strcmp( strbase, strtest ) != 0 )
      {
      fprintf(stderr,"STR", strbase, strtest);
      goto cleanup;
      }
    }

  same = 1;
  printf("STR");
cleanup:
  
  if(fbase) fclose(fbase);
  if(ftest) fclose(ftest);

  
  free(inParam.base_filename);
  free(inParam.test_filename);

  return same ? EXIT_SUCCESS : EXIT_FAILURE;
}