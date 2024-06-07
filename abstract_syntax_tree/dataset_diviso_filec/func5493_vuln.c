void OverlaySettings::save(QSettings* settings_ptr) {
	OverlaySettings def;

	SAVELOAD(bEnable, "STR");

	SAVELOAD(osShow, "STR");
	SAVELOAD(bAlwaysSelf, "STR");
	SAVELOAD(uiActiveTime, "STR");
	SAVELOAD(osSort, "STR");
	SAVELOAD(fX, "STR");
	SAVELOAD(fY, "STR");
	SAVELOAD(fZoom, "STR");
	SAVELOAD(uiColumns, "STR");

	settings_ptr->beginReadArray(QLatin1String("STR"));
	for (int i=0; i<4; ++i) {
		settings_ptr->setArrayIndex(i);
		SAVELOAD(qcUserName[i], "STR");
		SAVELOAD(fUser[i], "STR");
	}
	settings_ptr->endArray();

	SAVELOAD(qfUserName, "STR");
	SAVELOAD(qfChannel, "STR");
	SAVELOAD(qcChannel, "STR");
	SAVELOAD(qfFps, "STR");
	SAVELOAD(qcFps, "STR");

	SAVELOAD(fBoxPad, "STR");
	SAVELOAD(fBoxPenWidth, "STR");
	SAVELOAD(qcBoxPen, "STR");
	SAVELOAD(qcBoxFill, "STR");

	SAVELOAD(bUserName, "STR");
	SAVELOAD(bChannel, "STR");
	SAVELOAD(bMutedDeafened, "STR");
	SAVELOAD(bAvatar, "STR");
	SAVELOAD(bBox, "STR");
	SAVELOAD(bFps, "STR");

	SAVELOAD(fUserName, "STR");
	SAVELOAD(fChannel, "STR");
	SAVELOAD(fMutedDeafened, "STR");
	SAVELOAD(fAvatar, "STR");
	SAVELOAD(fFps, "STR");

	SAVELOAD(qrfUserName, "STR");
	SAVELOAD(qrfChannel, "STR");
	SAVELOAD(qrfMutedDeafened, "STR");
	SAVELOAD(qrfAvatar, "STR");
	SAVELOAD(qrfFps, "STR");

	SAVEFLAG(qaUserName, "STR");
	SAVEFLAG(qaChannel, "STR");
	SAVEFLAG(qaMutedDeafened, "STR");
	SAVEFLAG(qaAvatar, "STR");

	settings_ptr->setValue(QLatin1String("STR"), bUseWhitelist);
	settings_ptr->setValue(QLatin1String("STR"), qslBlacklist);
	settings_ptr->setValue(QLatin1String("STR"), qslWhitelist);
}