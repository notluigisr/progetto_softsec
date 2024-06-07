Runtime::LoaderPtr InstanceUtil::createRuntime(Instance& server,
                                               Server::Configuration::Initial& config) {
  ENVOY_LOG(info, "STR", MessageUtil::getYamlStringFromMessage(config.runtime()));
  return std::make_unique<Runtime::LoaderImpl>(
      server.dispatcher(), server.threadLocal(), config.runtime(), server.localInfo(),
      server.stats(), server.random(), server.messageValidationContext().dynamicValidationVisitor(),
      server.api());
}