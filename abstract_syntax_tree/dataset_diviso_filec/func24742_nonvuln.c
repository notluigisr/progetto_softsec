void PSOutputDev::setupEmbeddedTrueTypeFont(GfxFont *font, Ref *id,
					    GooString *psName) {
  char *fontBuf;
  int fontLen;
  FoFiTrueType *ffTT;
  Gushort *codeToGID;
  int i;

  
  for (i = 0; i < fontFileIDLen; ++i) {
    if (fontFileIDs[i].num == id->num &&
	fontFileIDs[i].gen == id->gen) {
      psName->appendf("STR", nextTrueTypeNum++);
      break;
    }
  }

  
  if (i == fontFileIDLen) {
    if (fontFileIDLen >= fontFileIDSize) {
      fontFileIDSize += 64;
      fontFileIDs = (Ref *)greallocn(fontFileIDs, fontFileIDSize, sizeof(Ref));
    }
    fontFileIDs[fontFileIDLen++] = *id;
  }

  
  writePSFmt("STR", psName);
  embFontList->append("STR");
  embFontList->append(psName->getCString());
  embFontList->append("STR");

  
  fontBuf = font->readEmbFontFile(xref, &fontLen);
  if ((ffTT = FoFiTrueType::make(fontBuf, fontLen))) {
    codeToGID = ((Gfx8BitFont *)font)->getCodeToGIDMap(ffTT);
    ffTT->convertToType42(psName->getCString(),
			  ((Gfx8BitFont *)font)->getHasEncoding()
			    ? ((Gfx8BitFont *)font)->getEncoding()
			    : (char **)NULL,
			  codeToGID, outputFunc, outputStream);
    if (codeToGID) {
      if (font8InfoLen >= font8InfoSize) {
	font8InfoSize += 16;
	font8Info = (PSFont8Info *)greallocn(font8Info,
					     font8InfoSize,
					     sizeof(PSFont8Info));
      }
      font8Info[font8InfoLen].fontID = *font->getID();
      font8Info[font8InfoLen].codeToGID = codeToGID;
      ++font8InfoLen;
    }
    delete ffTT;
  }
  gfree(fontBuf);

  
  writePS("STR");
}