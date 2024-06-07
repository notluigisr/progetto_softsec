static int getbaseline (const Proto *f, int pc, int *basepc) {
  if (f->sizeabslineinfo == 0 || pc < f->abslineinfo[0].pc) {
    *basepc = -1;  
    return f->linedefined;
  }
  else {
    unsigned int i;
    if (pc >= f->abslineinfo[f->sizeabslineinfo - 1].pc)
      i = f->sizeabslineinfo - 1;  
    else {  
      unsigned int j = f->sizeabslineinfo - 1;  
      i = 0;  
      while (i < j - 1) {
        unsigned int m = (j + i) / 2;
        if (pc >= f->abslineinfo[m].pc)
          i = m;
        else
          j = m;
      }
    }
    *basepc = f->abslineinfo[i].pc;
    return f->abslineinfo[i].line;
  }
}