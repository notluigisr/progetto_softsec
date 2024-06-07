rngOneTest(const char *sch,
               const char *filename,
               const char *result,
	       const char *err,
	       int options,
	       xmlRelaxNGPtr schemas) {
    xmlDocPtr doc;
    xmlRelaxNGValidCtxtPtr ctxt;
    int ret = 0;
    char *temp;
    FILE *schemasOutput;

    doc = xmlReadFile(filename, NULL, options);
    if (doc == NULL) {
        fprintf(stderr, "STR", filename, sch);
	return(-1);
    }

    temp = resultFilename(result, "STR");
    if (temp == NULL) {
        fprintf(stderr, "STR");
        fatalError();
    }
    schemasOutput = fopen(temp, "STR");
    if (schemasOutput == NULL) {
	fprintf(stderr, "STR", temp);
	xmlFreeDoc(doc);
        free(temp);
	return(-1);
    }

    ctxt = xmlRelaxNGNewValidCtxt(schemas);
    xmlRelaxNGSetValidErrors(ctxt,
         (xmlRelaxNGValidityErrorFunc) testErrorHandler,
         (xmlRelaxNGValidityWarningFunc) testErrorHandler,
	 ctxt);
    ret = xmlRelaxNGValidateDoc(ctxt, doc);
    if (ret == 0) {
	testErrorHandler(NULL, "STR", filename);
    } else if (ret > 0) {
	testErrorHandler(NULL, "STR", filename);
    } else {
	testErrorHandler(NULL, "STR",
	       filename);
    }
    fclose(schemasOutput);
    ret = 0;
    if (result) {
	if (compareFiles(temp, result)) {
	    fprintf(stderr, "STR", filename, sch);
	    ret = 1;
	}
    }
    if (temp != NULL) {
        unlink(temp);
        free(temp);
    }

    if (err != NULL) {
	if (compareFileMem(err, testErrors, testErrorsSize)) {
	    fprintf(stderr, "STR", filename, sch);
	    ret = 1;
	    printf("STR", testErrors);
	}
    }


    xmlRelaxNGFreeValidCtxt(ctxt);
    xmlFreeDoc(doc);
    return(ret);
}