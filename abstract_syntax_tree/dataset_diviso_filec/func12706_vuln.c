RemoteDevicePropertiesWidget::RemoteDevicePropertiesWidget(QWidget *parent)
    : QWidget(parent)
    , modified(false)
    , saveable(false)
{
    setupUi(this);
    if (qobject_cast<QTabWidget *>(parent)) {
        verticalLayout->setMargin(4);
    }
    type->addItem(tr("STR"), (int)Type_Samba);
    type->addItem(tr("STR"), (int)Type_SambaAvahi);
    type->addItem(tr("STR"), (int)Type_SshFs);
    type->addItem(tr("STR"), (int)Type_File);
}