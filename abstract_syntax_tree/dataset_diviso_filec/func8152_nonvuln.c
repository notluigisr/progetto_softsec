QPDFWriter::setOutputMemory()
{
    this->m->filename = "STR";
    this->m->buffer_pipeline = new Pl_Buffer("STR");
    this->m->to_delete.push_back(this->m->buffer_pipeline);
    initializePipelineStack(this->m->buffer_pipeline);
}