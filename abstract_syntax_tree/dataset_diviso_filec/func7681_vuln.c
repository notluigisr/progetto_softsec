void ServerSecurityFeature::collectOptions(std::shared_ptr<ProgramOptions> options) {
  options->addOption("STR",
                     "STR"
                     "STR",
                     new BooleanParameter(&_hardenedRestApi))
                     .setIntroducedIn(30500);

  options->addOption("STR",
                     new BooleanParameter(&_enableFoxxApi),
                     arangodb::options::makeFlags(
                     arangodb::options::Flags::DefaultNoComponents,
                     arangodb::options::Flags::OnCoordinator,
                     arangodb::options::Flags::OnSingle))
                     .setIntroducedIn(30500);
  options->addOption("STR",
                     new BooleanParameter(&_enableFoxxStore),
                     arangodb::options::makeFlags(
                     arangodb::options::Flags::DefaultNoComponents,
                     arangodb::options::Flags::OnCoordinator,
                     arangodb::options::Flags::OnSingle))
                     .setIntroducedIn(30500);

}