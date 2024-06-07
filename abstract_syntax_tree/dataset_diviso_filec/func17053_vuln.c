void FontInfoScanner::scanFonts(XRef *xrefA, Dict *resDict, std::vector<FontInfo*> *fontsList) {
  GfxFontDict *gfxFontDict;
  GfxFont *font;

  
  gfxFontDict = nullptr;
  const Object &fontObj = resDict->lookupNF("STR");
  if (fontObj.isRef()) {
    Object obj2 = fontObj.fetch(xrefA);
    if (obj2.isDict()) {
      Ref r = fontObj.getRef();
      gfxFontDict = new GfxFontDict(xrefA, &r, obj2.getDict());
    }
  } else if (fontObj.isDict()) {
    gfxFontDict = new GfxFontDict(xrefA, nullptr, fontObj.getDict());
  }
  if (gfxFontDict) {
    for (int i = 0; i < gfxFontDict->getNumFonts(); ++i) {
      if ((font = gfxFontDict->getFont(i))) {
        Ref fontRef = *font->getID();

        
        if (fonts.find(fontRef.num) == fonts.end()) {
	  fontsList->push_back(new FontInfo(font, xrefA));
          fonts.insert(fontRef.num);
        }
      }
    }
    delete gfxFontDict;
  }

  
  
  const char *resTypes[] = { "STR" };
  for (unsigned int resType = 0; resType < sizeof(resTypes) / sizeof(resTypes[0]); ++resType) {
    Object objDict = resDict->lookup(resTypes[resType]);
    if (objDict.isDict()) {
      for (int i = 0; i < objDict.dictGetLength(); ++i) {
        const Object &dictObjI = objDict.dictGetValNF(i);
        if (dictObjI.isRef()) {
          
          const Ref r = dictObjI.getRef();
          if (visitedObjects.find(r.num) != visitedObjects.end()) {
            continue;
          }

          visitedObjects.insert(r.num);
        }

        Object obj2 = dictObjI.fetch(xrefA);
        if (obj2.isStream()) {
          Object resObj = obj2.streamGetDict()->lookup("STR");
          if (resObj.isDict() && resObj.getDict() != resDict) {
            scanFonts(xrefA, resObj.getDict(), fontsList);
          }
        }
      }
    }
  }
}