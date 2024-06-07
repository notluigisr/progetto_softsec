void WebContents::OnDevToolsIndexingDone(int request_id,
                                         const std::string& file_system_path) {
  devtools_indexing_jobs_.erase(request_id);
  base::Value request_id_value(request_id);
  base::Value file_system_path_value(file_system_path);
  inspectable_web_contents_->CallClientFunction(
      "STR", &request_id_value, &file_system_path_value,
      nullptr);
}