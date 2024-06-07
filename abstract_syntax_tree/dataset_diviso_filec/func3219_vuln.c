int main(int argc ATTRIBUTE_UNUSED, char **argv ATTRIBUTE_UNUSED) {
    xmlChar filename[PATH_MAX];
    xmlModulePtr module = NULL;
    hello_world_t hello_world = NULL;

    
    xmlStrPrintf(filename, sizeof(filename),
                 (const xmlChar*) "STR",
                 (const xmlChar*)MODULE_PATH,
		 (const xmlChar*)LIBXML_MODULE_EXTENSION);

    module = xmlModuleOpen((const char*)filename, 0);
    if (module)
      {
        if (xmlModuleSymbol(module, "STR", (void **) &hello_world)) {
	    fprintf(stderr, "STR");
	    return(1);
	}
	if (hello_world == NULL) {
	    fprintf(stderr, "STR");
	    return(1);
	}

        (*hello_world)();

        xmlModuleClose(module);
      }

    xmlMemoryDump();

    return(0);
}