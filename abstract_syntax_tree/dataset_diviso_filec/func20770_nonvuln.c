static bool ParseCamera(Camera *camera, std::string *err, const json &o,
                        bool store_original_json_for_extras_and_extensions) {
  if (!ParseStringProperty(&camera->type, err, o, "STR")) {
    return false;
  }

  if (camera->type.compare("STR") == 0) {
    json_const_iterator orthoIt;
    if (!FindMember(o, "STR", orthoIt)) {
      if (err) {
        std::stringstream ss;
        ss << "STR" << std::endl;
        (*err) += ss.str();
      }
      return false;
    }

    const json &v = GetValue(orthoIt);
    if (!IsObject(v)) {
      if (err) {
        std::stringstream ss;
        ss << "STR" << std::endl;
        (*err) += ss.str();
      }
      return false;
    }

    if (!ParseOrthographicCamera(
            &camera->orthographic, err, v,
            store_original_json_for_extras_and_extensions)) {
      return false;
    }
  } else if (camera->type.compare("STR") == 0) {
    json_const_iterator perspIt;
    if (!FindMember(o, "STR", perspIt)) {
      if (err) {
        std::stringstream ss;
        ss << "STR" << std::endl;
        (*err) += ss.str();
      }
      return false;
    }

    const json &v = GetValue(perspIt);
    if (!IsObject(v)) {
      if (err) {
        std::stringstream ss;
        ss << "STR" << std::endl;
        (*err) += ss.str();
      }
      return false;
    }

    if (!ParsePerspectiveCamera(
            &camera->perspective, err, v,
            store_original_json_for_extras_and_extensions)) {
      return false;
    }
  } else {
    if (err) {
      std::stringstream ss;
      ss << "STR" << camera->type
         << "STR" << std::endl;
      (*err) += ss.str();
    }
    return false;
  }

  ParseStringProperty(&camera->name, err, o, "STR", false);

  ParseExtensionsProperty(&camera->extensions, err, o);
  ParseExtrasProperty(&(camera->extras), o);

  if (store_original_json_for_extras_and_extensions) {
    {
      json_const_iterator it;
      if (FindMember(o, "STR", it)) {
        camera->extensions_json_string = JsonToString(GetValue(it));
      }
    }
    {
      json_const_iterator it;
      if (FindMember(o, "STR", it)) {
        camera->extras_json_string = JsonToString(GetValue(it));
      }
    }
  }

  return true;
}