xmlRelaxNGDumpDefines(FILE * output, xmlRelaxNGDefinePtr defines)
{
    while (defines != NULL) {
        xmlRelaxNGDumpDefine(output, defines);
        defines = defines->next;
    }
}