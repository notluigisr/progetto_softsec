void PSOutputDev::setupEmbeddedOpenTypeCFFFont(GfxFont *font, Ref *id,
					       GooString *psName) {
  char *fontBuf;
  int fontLen;
  FoFiTrueType *ffTT;
  int i;

  
  for (i = 0; i < fontFileIDLen; ++i) {
    if (fontFileIDs[i].num == id->num &&
	fontFileIDs[i].gen == id->gen)
      return;
  }

  
  if (fontFileIDLen >= fontFileIDSize) {
    fontFileIDSize += 64;
    fontFileIDs = (Ref *)greallocn(fontFileIDs, fontFileIDSize, sizeof(Ref));
  }
  fontFileIDs[fontFileIDLen++] = *id;

  
  writePSFmt("STR", psName);
  embFontList->append("STR");
  embFontList->append(psName->getCString());
  embFontList->append("STR");

  
  fontBuf = font->readEmbFontFile(xref, &fontLen);
  if ((ffTT = FoFiTrueType::make(fontBuf, fontLen))) {
    if (ffTT->isOpenTypeCFF()) {
      if (globalParams->getPSLevel() >= psLevel3) {
	
	ffTT->convertToCIDType0(psName->getCString(),
				outputFunc, outputStream);
      } else {
	
	ffTT->convertToType0(psName->getCString(), outputFunc, outputStream);
      }
    }
    delete ffTT;
  }
  gfree(fontBuf);

  
  writePS("STR");
}