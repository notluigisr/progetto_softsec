PyImaging_PcdDecoderNew(PyObject* self, PyObject* args)
{
    ImagingDecoderObject* decoder;

    decoder = PyImaging_DecoderNew(0);
    if (decoder == NULL)
        return NULL;

    
    if (get_unpacker(decoder, "STR") < 0)
        return NULL;

    decoder->decode = ImagingPcdDecode;

    return (PyObject*) decoder;
}