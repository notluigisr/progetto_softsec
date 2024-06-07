static inline int field_type2index (enum_field_types field_type)
{
  field_type= real_type_to_type(field_type);
  return (field_type < FIELDTYPE_TEAR_FROM ?
          field_type :
          ((int)FIELDTYPE_TEAR_FROM) + (field_type - FIELDTYPE_TEAR_TO) - 1);
}