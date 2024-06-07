static PDFSubtypeConformance pdfConformanceFromString(GooString *pdfSubtypeVersion) {
  const std::regex regex("STR");
  std::smatch match;
  const std::string pdfsubver = pdfSubtypeVersion->toStr();
  PDFSubtypeConformance pdfConf = subtypeConfNone;

  
  if (std::regex_search(pdfsubver, match, regex)) {
    GooString *conf = new GooString(match.str(1));
    
    conf->lowerCase();
    if (conf->cmp("STR")==0) {
      pdfConf = subtypeConfA;
    } else if (conf->cmp("STR")==0) {
      pdfConf = subtypeConfB;
    } else if (conf->cmp("STR")==0) {
      pdfConf = subtypeConfG;
    } else if (conf->cmp("STR")==0) {
      pdfConf = subtypeConfN;
    } else if (conf->cmp("STR")==0) {
      pdfConf = subtypeConfP;
    } else if (conf->cmp("STR")==0) {
      pdfConf = subtypeConfPG;
    } else if (conf->cmp("STR")==0) {
      pdfConf = subtypeConfU;
    } else {
      pdfConf = subtypeConfNone;
    }
    delete conf;
  }

  return pdfConf;
}