void Krecipes::kreDBImport()
{
	QPointer<DBImportDialog> importOptions = new DBImportDialog;
	if ( importOptions->exec() == QDialog::Accepted ) {
		
		QString host, user, pass, table;
		int port;
		importOptions->serverParams( host, user, pass, port, table );

		KreDBImporter importer( importOptions->dbType(), host, user, pass, port ); 

		parsing_file_dlg->show();
		KApplication::setOverrideCursor( Qt::WaitCursor );
		QStringList tables;
		if ( importOptions->dbType() == "STR" )
			tables << importOptions->dbFile();
		else 
			tables << table;
		importer.parseFiles( tables );
		parsing_file_dlg->hide();
		KApplication::restoreOverrideCursor();

		KConfigGroup grp(KGlobal::config(),"STR");
		bool direct = grp.readEntry( "STR", false );
		if ( !direct ) {
			QPointer<RecipeImportDialog> import_dialog = new RecipeImportDialog( importer.recipeList() );

			if ( import_dialog->exec() != QDialog::Accepted ) {
				delete import_dialog;
				return;
			}
			else
				importer.setRecipeList( import_dialog->getSelectedRecipes() );

			delete import_dialog;

		}

		QString error = importer.getErrorMsg();
		if ( !error.isEmpty() ) {
			KMessageBox::sorry( this, error );
		}
		else
			importer.import(m_view->database);
	}
	delete importOptions;
}