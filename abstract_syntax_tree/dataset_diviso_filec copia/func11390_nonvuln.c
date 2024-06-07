int wav_read_frames(pcm_reader_t *preader, void *buffer, unsigned nframes)
{
    int rc;
    unsigned nbytes;
    wav_reader_t *reader = (wav_reader_t *)preader;

    if (!reader->ignore_length && nframes > reader->length - reader->position)
        nframes = reader->length - reader->position;
    nbytes = nframes * reader->sample_format.bytes_per_frame;
    if (nbytes) {
        if ((rc = pcm_read(&reader->io, buffer, nbytes)) < 0)
            return -1;
        nframes = rc / reader->sample_format.bytes_per_frame;
        reader->position += nframes;
    }
    return nframes;
}