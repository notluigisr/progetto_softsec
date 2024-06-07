std::map<std::string, std::string> GetAddedFileSystemPaths(
    content::WebContents* web_contents) {
  auto* pref_service = GetPrefService(web_contents);
  const base::Value* file_system_paths_value =
      pref_service->GetDictionary(prefs::kDevToolsFileSystemPaths);
  std::map<std::string, std::string> result;
  if (file_system_paths_value) {
    const base::DictionaryValue* file_system_paths_dict;
    file_system_paths_value->GetAsDictionary(&file_system_paths_dict);

    for (auto it : file_system_paths_dict->DictItems()) {
      std::string type =
          it.second.is_string() ? it.second.GetString() : std::string();
      result[it.first] = type;
    }
  }
  return result;
}