Status GraphConstructor::EnsureNoNameCollisions() {
  existing_nodes_.reserve(g_->num_nodes());
  
  for (Node* n : g_->nodes()) {
    bool already_exists = !existing_nodes_.insert({n->name(), n}).second;
    if (already_exists) {
      if (NodeNameInValues(opts_.input_map, n->name())) {
        return errors::InvalidArgument(
            "STR",
            n->name(), "STR");
      }
      if (NodeNameInValues(opts_.control_dependencies, n->name())) {
        return errors::InvalidArgument(
            "STR"
            "STR",
            n->name(), "STR");
      }
    }
    AddPrefixes(n->name(), &existing_prefixes_);
  }
  if (prefix_.empty() && opts_.importing && !opts_.uniquify_names) {
    for (size_t i = 0; i < node_def_count(); ++i) {
      const string& name = get_node_def(i).name();
      if (NameExistsInGraph(name)) {
        return errors::InvalidArgument("STR", name,
                                       "STR");
      }
    }
  } else if (!prefix_.empty()) {
    StringPiece prefix_no_slash(prefix_);
    prefix_no_slash.remove_suffix(1);
    if (!IsValidNodeName(prefix_no_slash, false)) {
      return errors::InvalidArgument("STR", prefix_,
                                     "STR");
    }
    if (NameExistsInGraph(prefix_no_slash) && opts_.uniquify_prefix) {
      prefix_ = strings::StrCat(FindUniqueName(prefix_no_slash), "STR");
    }
  }
  return Status::OK();
}