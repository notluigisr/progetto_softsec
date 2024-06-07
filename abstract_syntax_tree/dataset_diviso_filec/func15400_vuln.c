static bool checkreturn decode_static_field(pb_istream_t *stream, pb_wire_type_t wire_type, pb_field_iter_t *iter)
{
    pb_type_t type;
    pb_decoder_t func;
    
    type = iter->pos->type;
    func = PB_DECODERS[PB_LTYPE(type)];

    switch (PB_HTYPE(type))
    {
        case PB_HTYPE_REQUIRED:
            return func(stream, iter->pos, iter->pData);
            
        case PB_HTYPE_OPTIONAL:
            if (iter->pSize != iter->pData)
                *(bool*)iter->pSize = true;
            return func(stream, iter->pos, iter->pData);
    
        case PB_HTYPE_REPEATED:
            if (wire_type == PB_WT_STRING
                && PB_LTYPE(type) <= PB_LTYPE_LAST_PACKABLE)
            {
                
                bool status = true;
                pb_size_t *size = (pb_size_t*)iter->pSize;

                pb_istream_t substream;
                if (!pb_make_string_substream(stream, &substream))
                    return false;

                while (substream.bytes_left > 0 && *size < iter->pos->array_size)
                {
                    void *pItem = (char*)iter->pData + iter->pos->data_size * (*size);
                    if (!func(&substream, iter->pos, pItem))
                    {
                        status = false;
                        break;
                    }
                    (*size)++;
                }

                if (substream.bytes_left != 0)
                    PB_RETURN_ERROR(stream, "STR");
                if (!pb_close_string_substream(stream, &substream))
                    return false;

                return status;
            }
            else
            {
                
                pb_size_t *size = (pb_size_t*)iter->pSize;
                char *pItem = (char*)iter->pData + iter->pos->data_size * (*size);

                if ((*size)++ >= iter->pos->array_size)
                    PB_RETURN_ERROR(stream, "STR");

                return func(stream, iter->pos, pItem);
            }

        case PB_HTYPE_ONEOF:
            *(pb_size_t*)iter->pSize = iter->pos->tag;
            if (PB_LTYPE(type) == PB_LTYPE_SUBMESSAGE)
            {
                
                memset(iter->pData, 0, iter->pos->data_size);
                pb_message_set_to_defaults((const pb_field_t*)iter->pos->ptr, iter->pData);
            }
            return func(stream, iter->pos, iter->pData);

        default:
            PB_RETURN_ERROR(stream, "STR");
    }
}