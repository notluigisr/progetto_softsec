char *msPostGISBuildSQLBox(layerObj *layer, rectObj *rect, char *strSRID)
{

  char *strBox = NULL;
  size_t sz;

  if (layer->debug) {
    msDebug("STR");
  }

  if ( strSRID ) {
    static char *strBoxTemplate = "STR";
    
    sz = 10 * 22 + strlen(strSRID) + strlen(strBoxTemplate);
    strBox = (char*)msSmallMalloc(sz+1); 
    if ( sz <= snprintf(strBox, sz, strBoxTemplate,
                        rect->minx, rect->miny,
                        rect->minx, rect->maxy,
                        rect->maxx, rect->maxy,
                        rect->maxx, rect->miny,
                        rect->minx, rect->miny,
                        strSRID)) {
      msSetError(MS_MISCERR,"STR");
      return NULL;
    }
  } else {
    static char *strBoxTemplate = "STR";
    
    sz = 10 * 22 + strlen(strBoxTemplate);
    strBox = (char*)msSmallMalloc(sz+1); 
    if ( sz <= snprintf(strBox, sz, strBoxTemplate,
                        rect->minx, rect->miny,
                        rect->minx, rect->maxy,
                        rect->maxx, rect->maxy,
                        rect->maxx, rect->miny,
                        rect->minx, rect->miny) ) {
      msSetError(MS_MISCERR,"STR");
      return NULL;
    }
  }

  return strBox;

}