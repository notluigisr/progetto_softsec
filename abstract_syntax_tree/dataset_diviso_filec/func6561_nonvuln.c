bool Shortcut::isServerSpecific() const {
	if (qvData.canConvert<ShortcutTarget>()) {
		const ShortcutTarget &sc = qvariant_cast<ShortcutTarget> (qvData);
		return sc.isServerSpecific();
	}
	return false;
}