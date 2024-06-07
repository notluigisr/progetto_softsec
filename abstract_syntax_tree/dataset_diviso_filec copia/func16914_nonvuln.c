write_indexes (LZWDecoder *self,
               guint8     *output,
               gsize       output_length)
{
        int c;
        gsize index_count = 1, offset;

        
        if (self->code >= self->code_table_size)
                return 0;

        
        c = self->code;
        while (self->code_table[c].extends != self->eoi_code) {
                c = self->code_table[c].extends;
                index_count++;
        }

        
        c = self->code;
        offset = index_count - 1;
        while (TRUE) {
                if (offset < output_length)
                        output[offset] = self->code_table[c].index;

                if (self->code_table[c].extends == self->eoi_code)
                        return index_count;

                c = self->code_table[c].extends;
                offset--;
        }
}