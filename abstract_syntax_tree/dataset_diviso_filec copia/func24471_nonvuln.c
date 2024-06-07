Status RestoreSession(const RunOptions& run_options,
                      const MetaGraphDef& meta_graph, const string& export_dir,
                      std::unique_ptr<Session>* session) {
  const uint64 read_start_microseconds = Env::Default()->NowMicros();
  std::vector<AssetFileDef> asset_file_defs;
  TF_RETURN_IF_ERROR(internal::GetAssetFileDefs(meta_graph, &asset_file_defs));
  TF_RETURN_IF_ERROR(RunRestore(run_options, export_dir,
                                meta_graph.saver_def().restore_op_name(),
                                meta_graph.saver_def().filename_tensor_name(),
                                asset_file_defs, session->get()));
  
  
  const uint64 restore_graph_walltime =
      GetLatencyMicroseconds(read_start_microseconds);

  const uint64 graph_init_start_microseconds = Env::Default()->NowMicros();
  string init_op_name;
  TF_RETURN_IF_ERROR(
      internal::GetInitOp(export_dir, meta_graph, &init_op_name));
  TF_RETURN_IF_ERROR(RunInitOp(run_options, export_dir, meta_graph,
                               asset_file_defs, session->get(), init_op_name));
  load_latency_by_stage->GetCell(export_dir, "STR")
      ->Add(restore_graph_walltime);
  
  load_latency_by_stage->GetCell(export_dir, "STR")
      ->Add(GetLatencyMicroseconds(graph_init_start_microseconds));
  return Status::OK();
}