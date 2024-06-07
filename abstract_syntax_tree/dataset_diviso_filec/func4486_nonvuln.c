Wasm::Wasm(absl::string_view vm, absl::string_view vm_id, absl::string_view vm_configuration,
           PluginSharedPtr plugin, Stats::ScopeSharedPtr scope,
           Upstream::ClusterManager& cluster_manager, Event::Dispatcher& dispatcher)
    : vm_id_(std::string(vm_id)), wasm_vm_(Common::Wasm::createWasmVm(vm)), plugin_(plugin),
      scope_(scope), cluster_manager_(cluster_manager), dispatcher_(dispatcher),
      time_source_(dispatcher.timeSource()), vm_configuration_(vm_configuration),
      stat_name_set_(scope_->symbolTable().makeSet("STR").release()) {}