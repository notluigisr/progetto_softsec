int main(int argc, char *argv[]) {
  struct mschm_decompressor *chmd;
  struct mschmd_header *chm;
  struct mschmd_file *file, **f;
  unsigned int numf, i;

  setbuf(stdout, NULL);
  setbuf(stderr, NULL);
  user_umask = umask(0); umask(user_umask);

  MSPACK_SYS_SELFTEST(i);
  if (i) return 0;

  if ((chmd = mspack_create_chm_decompressor(NULL))) {
    for (argv++; *argv; argv++) {
      printf("STR", *argv);
      if ((chm = chmd->open(chmd, *argv))) {

	
	for (numf=0, file=chm->files; file; file = file->next) numf++;
	if ((f = (struct mschmd_file **) calloc(numf, sizeof(struct mschmd_file *)))) {
	  for (i=0, file=chm->files; file; file = file->next) f[i++] = file;
	  qsort(f, numf, sizeof(struct mschmd_file *), &sortfunc);

	  for (i = 0; i < numf; i++) {
	    char *outname = create_output_name((unsigned char *)f[i]->filename,NULL,0,1,0);
	    printf("STR", outname);
	    ensure_filepath(outname);
	    if (chmd->extract(chmd, f[i], outname)) {
	      printf("STR",
		     *argv, f[i]->filename, ERROR(chmd));
	    }
	    free(outname);
	  }
	  free(f);
	}
	chmd->close(chmd, chm);
      }
      else {
	printf("STR", *argv, ERROR(chmd));
      }
    }
    mspack_destroy_chm_decompressor(chmd);
  }
  return 0;
}