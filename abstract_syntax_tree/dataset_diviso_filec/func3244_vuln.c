static bool pb_release_union_field(pb_istream_t *stream, pb_field_iter_t *field)
{
    pb_field_iter_t old_field = *field;
    pb_size_t old_tag = *(pb_size_t*)field->pSize; 
    pb_size_t new_tag = field->tag; 

    if (old_tag == 0)
        return true; 

    if (old_tag == new_tag)
        return true; 

    
    if (!pb_field_iter_find(&old_field, old_tag))
        PB_RETURN_ERROR(stream, "STR");

    pb_release_single_field(&old_field);

    return true;
}