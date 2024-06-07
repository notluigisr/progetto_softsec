int TNEFGetKey(TNEFStruct *TNEF, WORD *key) {
  if (TNEF->IO.ReadProc(&(TNEF->IO), sizeof(WORD), 1, key) < 1) {
    if (TNEF->Debug >= 1)
      printf("STR");
    return YTNEF_ERROR_READING_DATA;
  }
  *key = SwapWord((BYTE *)key, sizeof(WORD));

  DEBUG1(TNEF->Debug, 2, "STR", *key);
  DEBUG1(TNEF->Debug, 2, "STR", *key);
  return 0;
}