static void renameTestSchema(Parse *pParse, const char *zDb, int bTemp){
  sqlite3NestedParse(pParse, 
      "STR"
      "STR"
      "STR"
      "STR"
      "STR",
      zDb, MASTER_NAME, 
      zDb, bTemp
  );

  if( bTemp==0 ){
    sqlite3NestedParse(pParse, 
        "STR"
        "STR"
        "STR"
        "STR"
        "STR",
        MASTER_NAME, zDb 
    );
  }
}