static int reglevel (FuncState *fs, int nvar) {
  while (nvar-- > 0) {
    Vardesc *vd = getlocalvardesc(fs, nvar);  
    if (vd->vd.kind != RDKCTC)  
      return vd->vd.ridx + 1;
  }
  return 0;  
}