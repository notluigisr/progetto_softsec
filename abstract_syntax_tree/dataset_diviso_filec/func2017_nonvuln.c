void PSOutputDev::updateFillColor(GfxState *state) {
  GfxColor color;
  GfxColor *colorPtr;
  GfxGray gray;
  GfxCMYK cmyk;
  GfxSeparationColorSpace *sepCS;
  double c, m, y, k;
  int i;

  switch (level) {
  case psLevel1:
    state->getFillGray(&gray);
    writePSFmt("STR", colToDbl(gray));
    break;
  case psLevel1Sep:
    state->getFillCMYK(&cmyk);
    c = colToDbl(cmyk.c);
    m = colToDbl(cmyk.m);
    y = colToDbl(cmyk.y);
    k = colToDbl(cmyk.k);
    writePSFmt("STR", c, m, y, k);
    addProcessColor(c, m, y, k);
    break;
  case psLevel2:
  case psLevel3:
    if (state->getFillColorSpace()->getMode() != csPattern) {
      colorPtr = state->getFillColor();
      writePS("STR");
      for (i = 0; i < state->getFillColorSpace()->getNComps(); ++i) {
	if (i > 0) {
	  writePS("STR");
      }
	writePSFmt("STR", colToDbl(colorPtr->c[i]));
      }
      writePS("STR");
    }
    break;
  case psLevel2Sep:
  case psLevel3Sep:
    if (state->getFillColorSpace()->getMode() == csSeparation) {
      sepCS = (GfxSeparationColorSpace *)state->getFillColorSpace();
      color.c[0] = gfxColorComp1;
      sepCS->getCMYK(&color, &cmyk);
      writePSFmt("STR",
		 colToDbl(state->getFillColor()->c[0]),
		 colToDbl(cmyk.c), colToDbl(cmyk.m),
		 colToDbl(cmyk.y), colToDbl(cmyk.k),
		 sepCS->getName());
      addCustomColor(sepCS);
    } else {
      state->getFillCMYK(&cmyk);
      c = colToDbl(cmyk.c);
      m = colToDbl(cmyk.m);
      y = colToDbl(cmyk.y);
      k = colToDbl(cmyk.k);
      writePSFmt("STR", c, m, y, k);
      addProcessColor(c, m, y, k);
    }
    break;
  }
  t3Cacheable = gFalse;
}