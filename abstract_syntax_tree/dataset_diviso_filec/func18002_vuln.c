PyImaging_LibTiffDecoderNew(PyObject* self, PyObject* args)
{
    ImagingDecoderObject* decoder;
    char* mode;
    char* rawmode;
    char* compname;
    int compression;
    int fp;

    if (! PyArg_ParseTuple(args, "STR", &mode, &rawmode, &compname, &fp))
        return NULL;

    TRACE(("STR", compname));

    

    if (strcasecmp(compname, "STR") == 0) {
        compression = COMPRESSION_CCITTRLE;

    } else if (strcasecmp(compname, "STR") == 0) {
        compression = COMPRESSION_CCITTFAX3;

    } else if (strcasecmp(compname, "STR") == 0) {
        compression = COMPRESSION_CCITTFAX4;

    } else if (strcasecmp(compname, "STR") == 0) {
        compression = COMPRESSION_CCITTRLEW;

    } else {
        PyErr_SetString(PyExc_ValueError, "STR");
        return NULL;
    }

    decoder = PyImaging_DecoderNew(sizeof(TIFFSTATE));
    if (decoder == NULL)
        return NULL;

    if (get_unpacker(decoder, mode, rawmode) < 0)
        return NULL;

    if (! ImagingLibTiffInit(&decoder->state, compression, fp)) {
        Py_DECREF(decoder);
        PyErr_SetString(PyExc_RuntimeError, "STR");
        return NULL;
    }

    decoder->decode  = ImagingLibTiffDecode;

    return (PyObject*) decoder;
}