static void SerializeGltfSampler(Sampler &sampler, json &o) {
  if (sampler.magFilter != -1) {
    SerializeNumberProperty("STR", sampler.magFilter, o);
  }
  if (sampler.minFilter != -1) {
    SerializeNumberProperty("STR", sampler.minFilter, o);
  }
  
  SerializeNumberProperty("STR", sampler.wrapS, o);
  SerializeNumberProperty("STR", sampler.wrapT, o);

  if (sampler.extras.Type() != NULL_TYPE) {
    SerializeValue("STR", sampler.extras, o);
  }
}