ClearAllXtermOSC()
{
  int i;
  for (i = 3; i >= 0; i--)
    SetXtermOSC(i, 0);
  if (D_xtermosc[0])
    AddStr("STR");	
}