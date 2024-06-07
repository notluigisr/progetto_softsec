void WebContents::DevToolsIndexPath(
    int request_id,
    const std::string& file_system_path,
    const std::string& excluded_folders_message) {
  if (!IsDevToolsFileSystemAdded(GetDevToolsWebContents(), file_system_path)) {
    OnDevToolsIndexingDone(request_id, file_system_path);
    return;
  }
  if (devtools_indexing_jobs_.count(request_id) != 0)
    return;
  std::vector<std::string> excluded_folders;
  std::unique_ptr<base::Value> parsed_excluded_folders =
      base::JSONReader::ReadDeprecated(excluded_folders_message);
  if (parsed_excluded_folders && parsed_excluded_folders->is_list()) {
    for (const base::Value& folder_path :
         parsed_excluded_folders->GetListDeprecated()) {
      if (folder_path.is_string())
        excluded_folders.push_back(folder_path.GetString());
    }
  }
  devtools_indexing_jobs_[request_id] =
      scoped_refptr<DevToolsFileSystemIndexer::FileSystemIndexingJob>(
          devtools_file_system_indexer_->IndexPath(
              file_system_path, excluded_folders,
              base::BindRepeating(
                  &WebContents::OnDevToolsIndexingWorkCalculated,
                  weak_factory_.GetWeakPtr(), request_id, file_system_path),
              base::BindRepeating(&WebContents::OnDevToolsIndexingWorked,
                                  weak_factory_.GetWeakPtr(), request_id,
                                  file_system_path),
              base::BindRepeating(&WebContents::OnDevToolsIndexingDone,
                                  weak_factory_.GetWeakPtr(), request_id,
                                  file_system_path)));
}