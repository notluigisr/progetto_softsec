int findDirUplevelToDirContainingFile(J9StringBuffer **result, char *pathEnvar, char pathSeparator, char *fileInPath, int upLevels, int elementsToSkip) {
	char *paths;
	int   rc;

	
	paths = getenv(pathEnvar);
	if (!paths) {
		return FALSE;
	}

	
	rc = findDirContainingFile(result, paths, pathSeparator, fileInPath, elementsToSkip);

	
	if (rc) {
		for (; upLevels > 0; upLevels--) {
			truncatePath(jvmBufferData(*result));
		}
	}
   return rc;
}