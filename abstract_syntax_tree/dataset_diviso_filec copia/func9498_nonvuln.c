  Context* getRootContext(absl::string_view root_id) { return root_contexts_[root_id].get(); }