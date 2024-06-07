void mobi_free_opf(OPF *opf) {
    mobi_free_opf_metadata(opf->metadata);
    mobi_free_opf_manifest(opf->manifest);
    mobi_free_opf_spine(opf->spine);
    mobi_free_opf_guide(opf->guide);
}