long vorbis_book_decodevs_add(codebook *book,float *a,oggpack_buffer *b,int n){
  if(book->used_entries>0){
    int step=n/book->dim;
    long *entry = alloca(sizeof(*entry)*step);
    float **t = alloca(sizeof(*t)*step);
    int i,j,o;

    for (i = 0; i < step; i++) {
      entry[i]=decode_packed_entry_number(book,b);
      if(entry[i]==-1)return(-1);
      t[i] = book->valuelist+entry[i]*book->dim;
    }
    for(i=0,o=0;i<book->dim;i++,o+=step)
      for (j=0;j<step;j++)
        a[o+j]+=t[j][i];
  }
  return(0);
}