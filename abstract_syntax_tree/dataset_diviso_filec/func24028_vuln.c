SetXtermOSC(i, s)
int i;
char *s;
{
  static char *oscs[][2] = {
    { WT_FLAG "STR" }, 
    { "STR" },      
    { "STR" }, 
    { "STR" }  
  };

  ASSERT(display);
  if (!D_CXT)
    return;
  if (!s)
    s = "";
  if (!D_xtermosc[i] && !*s)
    return;
  if (i == 0 && !D_xtermosc[0])
    AddStr("STR");	
  if (!*s)
    s = oscs[i][1];
  D_xtermosc[i] = 1;
  AddStr("STR");
  AddStr(oscs[i][0]);
  AddStr(s);
  AddChar(7);
}