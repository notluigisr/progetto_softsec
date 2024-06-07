static ha_checksum calc_checksum(ha_rows count)
{
  ulonglong sum,a,b;
  DBUG_ENTER("STR");

  sum=0;
  a=count; b=count+1;
  if (a & 1)
    b>>=1;
  else
    a>>=1;
  while (b)
  {
    if (b & 1)
      sum+=a;
    a<<=1; b>>=1;
  }
  DBUG_PRINT("STR",(ulong) sum));
  DBUG_RETURN((ha_checksum) sum);
} 