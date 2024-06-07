static bool ParseSampler(Sampler *sampler, std::string *err, const json &o,
                         bool store_original_json_for_extras_and_extensions) {
  ParseStringProperty(&sampler->name, err, o, "STR", false);

  int minFilter = -1;
  int magFilter = -1;
  int wrapS = TINYGLTF_TEXTURE_WRAP_REPEAT;
  int wrapT = TINYGLTF_TEXTURE_WRAP_REPEAT;
  
  ParseIntegerProperty(&minFilter, err, o, "STR", false);
  ParseIntegerProperty(&magFilter, err, o, "STR", false);
  ParseIntegerProperty(&wrapS, err, o, "STR", false);
  ParseIntegerProperty(&wrapT, err, o, "STR", false);
  

  
  

  sampler->minFilter = minFilter;
  sampler->magFilter = magFilter;
  sampler->wrapS = wrapS;
  sampler->wrapT = wrapT;
  

  ParseExtensionsProperty(&(sampler->extensions), err, o);
  ParseExtrasProperty(&(sampler->extras), o);

  if (store_original_json_for_extras_and_extensions) {
    {
      json_const_iterator it;
      if (FindMember(o, "STR", it)) {
        sampler->extensions_json_string = JsonToString(GetValue(it));
      }
    }
    {
      json_const_iterator it;
      if (FindMember(o, "STR", it)) {
        sampler->extras_json_string = JsonToString(GetValue(it));
      }
    }
  }

  return true;
}