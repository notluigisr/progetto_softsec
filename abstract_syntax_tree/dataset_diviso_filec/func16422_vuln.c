void t_cpp_generator::generate_struct_writer(ofstream& out, t_struct* tstruct, bool pointers) {
  string name = tstruct->get_name();
  const vector<t_field*>& fields = tstruct->get_sorted_members();
  vector<t_field*>::const_iterator f_iter;

  if (gen_templates_) {
    out << indent() << "STR"
        << tstruct->get_name() << "STR" << endl;
  } else {
    indent(out) << "STR" << tstruct->get_name()
                << "STR" << endl;
  }
  indent_up();

  out << indent() << "STR" << endl;

  indent(out) << "STR" << endl;
  indent(out) << "STR" << endl;

  for (f_iter = fields.begin(); f_iter != fields.end(); ++f_iter) {
    bool check_if_set = (*f_iter)->get_req() == t_field::T_OPTIONAL
                        || (*f_iter)->get_type()->is_xception();
    if (check_if_set) {
      out << endl << indent() << "STR" << endl;
      indent_up();
    } else {
      out << endl;
    }

    
    out << indent() << "STR"
        << "STR"
        << (*f_iter)->get_key() << "STR" << endl;
    
    if (pointers && !(*f_iter)->get_type()->is_xception()) {
      generate_serialize_field(out, *f_iter, "STR");
    } else {
      generate_serialize_field(out, *f_iter, "STR");
    }
    
    indent(out) << "STR" << endl;
    if (check_if_set) {
      indent_down();
      indent(out) << '}';
    }
  }

  out << endl;

  
  out << indent() << "STR" << endl << indent()
      << "STR" << endl << indent()
      << "STR" << endl;

  indent_down();
  indent(out) << "STR" << endl << endl;
}