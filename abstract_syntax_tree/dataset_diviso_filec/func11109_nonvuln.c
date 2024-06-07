void PSOutputDev::setupEmbeddedType1CFont(GfxFont *font, Ref *id,
					  GooString *psName) {
  char *fontBuf;
  int fontLen;
  FoFiType1C *ffT1C;
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
  if ((ffT1C = FoFiType1C::make(fontBuf, fontLen))) {
    ffT1C->convertToType1(psName->getCString(), NULL, gTrue,
			  outputFunc, outputStream);
    delete ffT1C;
  }
  gfree(fontBuf);

  
  writePS("STR");
}