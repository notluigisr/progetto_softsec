enum_field_types Field::field_type_merge(enum_field_types a,
                                         enum_field_types b)
{
  return field_types_merge_rules[field_type2index(a)]
                                [field_type2index(b)];
}