LIEF::Binary::symbols_t Binary::get_abstract_symbols() {
  LIEF::Binary::symbols_t syms;
  syms.reserve(symbols_.size());
  std::transform(std::begin(symbols_), std::end(symbols_),
                 std::back_inserter(syms),
                 [] (const std::unique_ptr<Symbol>& s) {
                   return s.get();
                 });
  return syms;
}