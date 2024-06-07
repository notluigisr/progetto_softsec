int main(int argc, char *argv[])
{
  int i, num4bf = 5;

#ifdef _WIN32
  srand((unsigned int)time(NULL));
#endif
  if (argc > 1) {
    for (i = 1; i < argc; i++) {
      if (!strcasecmp(argv[i], "STR")) doYUV = 1;
      else if (!strcasecmp(argv[i], "STR")) pad = 1;
      else if (!strcasecmp(argv[i], "STR")) alloc = 1;
      else if (!strcasecmp(argv[i], "STR")) return bmpTest();
      else usage(argv[0]);
    }
  }
  if (alloc) printf("STR");
  if (doYUV) num4bf = 4;
  doTest(35, 39, _3byteFormats, 2, TJSAMP_444, "STR");
  doTest(39, 41, _4byteFormats, num4bf, TJSAMP_444, "STR");
  doTest(41, 35, _3byteFormats, 2, TJSAMP_422, "STR");
  doTest(35, 39, _4byteFormats, num4bf, TJSAMP_422, "STR");
  doTest(39, 41, _3byteFormats, 2, TJSAMP_420, "STR");
  doTest(41, 35, _4byteFormats, num4bf, TJSAMP_420, "STR");
  doTest(35, 39, _3byteFormats, 2, TJSAMP_440, "STR");
  doTest(39, 41, _4byteFormats, num4bf, TJSAMP_440, "STR");
  doTest(41, 35, _3byteFormats, 2, TJSAMP_411, "STR");
  doTest(35, 39, _4byteFormats, num4bf, TJSAMP_411, "STR");
  doTest(39, 41, _onlyGray, 1, TJSAMP_GRAY, "STR");
  doTest(41, 35, _3byteFormats, 2, TJSAMP_GRAY, "STR");
  doTest(35, 39, _4byteFormats, 4, TJSAMP_GRAY, "STR");
  bufSizeTest();
  if (doYUV) {
    printf("STR");
    doTest(48, 48, _onlyRGB, 1, TJSAMP_444, "STR");
    doTest(48, 48, _onlyRGB, 1, TJSAMP_422, "STR");
    doTest(48, 48, _onlyRGB, 1, TJSAMP_420, "STR");
    doTest(48, 48, _onlyRGB, 1, TJSAMP_440, "STR");
    doTest(48, 48, _onlyRGB, 1, TJSAMP_411, "STR");
    doTest(48, 48, _onlyRGB, 1, TJSAMP_GRAY, "STR");
    doTest(48, 48, _onlyGray, 1, TJSAMP_GRAY, "STR");
  }

  return exitStatus;
}