HInstruction* HGraphBuilder::BuildMonomorphicElementAccess(HValue* object,
                                                           HValue* key,
                                                           HValue* val,
                                                           HValue* dependency,
                                                           Handle<Map> map,
                                                           bool is_store) {
  HCheckMaps* mapcheck = new(zone()) HCheckMaps(object, map,
                                                zone(), dependency);
  AddInstruction(mapcheck);
  if (dependency) {
    mapcheck->ClearGVNFlag(kDependsOnElementsKind);
  }
  return BuildUncheckedMonomorphicElementAccess(object, key, val,
                                                mapcheck, map, is_store);
}