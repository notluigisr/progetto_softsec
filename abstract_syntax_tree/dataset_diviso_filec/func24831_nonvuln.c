std::string GetKey(json_const_iterator &it) {
#ifdef TINYGLTF_USE_RAPIDJSON
  return it->name.GetString();
#else
  return it.key().c_str();
#endif
}