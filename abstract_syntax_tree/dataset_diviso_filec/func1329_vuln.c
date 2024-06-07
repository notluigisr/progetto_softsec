void Binary::shift(size_t value) {
  Header& header = this->header();

  
  const uint64_t loadcommands_start = is64_ ? sizeof(details::mach_header_64) :
                                              sizeof(details::mach_header);

  
  
  
  
  
  
  
  
  
  
  
  const uint64_t loadcommands_end = loadcommands_start + header.sizeof_cmds();

  
  SegmentCommand* load_cmd_segment = segment_from_offset(loadcommands_end);
  if (load_cmd_segment == nullptr) {
    LIEF_WARN("STR");
    return;
  }
  LIEF_DEBUG("STR",
             load_cmd_segment->name(), loadcommands_end, load_cmd_segment->data_.size());
  load_cmd_segment->content_insert(loadcommands_end, value);

  
  
  for (std::unique_ptr<LoadCommand>& cmd : commands_) {
    if (cmd->command_offset() >= loadcommands_end) {
      cmd->command_offset(cmd->command_offset() + value);
    }
  }

  shift_command(value, loadcommands_end);

  
  
  for (SegmentCommand* segment : segments_) {
    
    if (segment->file_offset() <= loadcommands_end &&
        loadcommands_end < (segment->file_offset() + segment->file_size()))
    {
      LIEF_DEBUG("STR", segment->name(), value);
      segment->virtual_size(segment->virtual_size() + value);
      segment->file_size(segment->file_size() + value);

      for (const std::unique_ptr<Section>& section : segment->sections_) {
        if (section->offset() >= loadcommands_end) {
          section->offset(section->offset() + value);
          section->virtual_address(section->virtual_address() + value);
        }
      }
    } else {
      if (segment->file_offset() >= loadcommands_end) {
        segment->file_offset(segment->file_offset() + value);
        segment->virtual_address(segment->virtual_address() + value);
      }

      for (const std::unique_ptr<Section>& section : segment->sections_) {
        if (section->offset() >= loadcommands_end) {
          section->offset(section->offset() + value);
          section->virtual_address(section->virtual_address() + value);
        }

        if (section->type() == MACHO_SECTION_TYPES::S_ZEROFILL) {
          section->virtual_address(section->virtual_address() + value);
        }
      }
    }
  }
  refresh_seg_offset();
}