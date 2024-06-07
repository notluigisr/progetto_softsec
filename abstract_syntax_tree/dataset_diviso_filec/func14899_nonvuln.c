void HGraph::EliminateRedundantBoundsChecks() {
  HPhase phase("STR", this);
  BoundsCheckTable checks_table(zone());
  EliminateRedundantBoundsChecks(entry_block(), &checks_table);
}