HEnvironment::HEnvironment(HEnvironment* outer,
                           Handle<JSFunction> closure,
                           FrameType frame_type,
                           int arguments,
                           Zone* zone)
    : closure_(closure),
      values_(arguments, zone),
      assigned_variables_(0, zone),
      frame_type_(frame_type),
      parameter_count_(arguments),
      local_count_(0),
      outer_(outer),
      entry_(NULL),
      pop_count_(0),
      push_count_(0),
      ast_id_(BailoutId::None()),
      zone_(zone) {
}