int msPostGISGetPaging(layerObj *layer)
{
#ifdef USE_POSTGIS
  msPostGISLayerInfo *layerinfo = NULL;

  if (layer->debug) {
    msDebug("STR");
  }

  if(!msPostGISLayerIsOpen(layer))
    return MS_TRUE;

  assert( layer->layerinfo != NULL);

  layerinfo = (msPostGISLayerInfo *)layer->layerinfo;
  return layerinfo->paging;
#else
  msSetError( MS_MISCERR,
              "STR",
              "STR");
  return MS_FAILURE;
#endif
}