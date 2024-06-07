HInstruction* HGraphBuilder::BuildLoadNamedMonomorphic(HValue* object,
                                                       Handle<String> name,
                                                       Property* expr,
                                                       Handle<Map> map) {
  
  ASSERT(!map->is_dictionary_map());
  LookupResult lookup(isolate());
  map->LookupDescriptor(NULL, *name, &lookup);
  if (lookup.IsField()) {
    return BuildLoadNamedField(object, map, &lookup, true);
  }

  
  if (lookup.IsConstantFunction()) {
    AddInstruction(new(zone()) HCheckNonSmi(object));
    AddInstruction(HCheckMaps::NewWithTransitions(object, map, zone()));
    Handle<JSFunction> function(lookup.GetConstantFunctionFromMap(*map));
    return new(zone()) HConstant(function, Representation::Tagged());
  }

  
  return BuildLoadNamedGeneric(object, name, expr);
}