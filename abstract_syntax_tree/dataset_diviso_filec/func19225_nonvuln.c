const Section* Binary::section_from_offset(uint64_t offset) const {
  const auto it_section = std::find_if(
      sections_.cbegin(), sections_.cend(),
      [offset] (const Section* section) {
        return section->offset() <= offset &&
               offset < (section->offset() + section->size());
      });

  if (it_section == sections_.cend()) {
    return nullptr;
  }

  return *it_section;
}