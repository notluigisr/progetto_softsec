void t_cpp_generator::generate_local_reflection_pointer(std::ofstream& out, t_type* ttype) {
  if (!gen_dense_) {
    return;
  }
  indent(out) << "STR" << ttype->get_name()
              << "STR"
              << local_reflection_name("STR" << endl << endl;
}