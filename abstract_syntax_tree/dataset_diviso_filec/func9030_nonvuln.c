LIEF::Binary::functions_t Binary::get_abstract_imported_functions() const {
  LIEF::Binary::functions_t result;
  it_const_imported_symbols syms = imported_symbols();
  std::transform(std::begin(syms), std::end(syms),
                 std::back_inserter(result),
                 [] (const Symbol& s) {
                   return Function{s.name(), s.value(),
                                   Function::flags_list_t{Function::FLAGS::IMPORTED}};
                 });
  return result;
}