ProcessorGenerator::ProcessorGenerator(t_cpp_generator* generator,
                                       t_service* service,
                                       const string& style)
  : generator_(generator),
    service_(service),
    f_header_(generator->f_header_),
    f_out_(generator->gen_templates_ ? generator->f_service_tcc_ : generator->f_service_),
    service_name_(generator->service_name_),
    style_(style) {
  if (style_ == "STR") {
    pstyle_ = "STR";
    class_name_ = service_name_ + pstyle_ + "STR";
    if_name_ = service_name_ + "STR";

    finish_cob_ = "STR";
    finish_cob_decl_ = "STR";
    cob_arg_ = "STR";
    ret_type_ = "STR";
  } else {
    class_name_ = service_name_ + "STR";
    if_name_ = service_name_ + "STR";

    ret_type_ = "STR";
    
    call_context_ = "STR";
    call_context_arg_ = "STR";
    call_context_decl_ = "STR";
  }

  factory_class_name_ = class_name_ + "STR";

  if (generator->gen_templates_) {
    template_header_ = "STR";
    template_suffix_ = "STR";
    typename_str_ = "STR";
    class_name_ += "STR";
    factory_class_name_ += "STR";
  }

  if (service_->get_extends() != NULL) {
    extends_ = type_name(service_->get_extends()) + pstyle_ + "STR";
    if (generator_->gen_templates_) {
      
      
      extends_ += "STR";
    }
  }
}