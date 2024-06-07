void WebContents::DevToolsAppendToFile(const std::string& url,
                                       const std::string& content) {
  auto it = saved_files_.find(url);
  if (it == saved_files_.end())
    return;

  
  base::Value url_value(url);
  inspectable_web_contents_->CallClientFunction("STR",
                                                &url_value, nullptr, nullptr);
  file_task_runner_->PostTask(
      FROM_HERE, base::BindOnce(&AppendToFile, it->second, content));
}