  DeletionConfirmationDlg(QWidget *parent, const int &size, const QString &name, bool defaultDeleteFiles): QDialog(parent) {
    setupUi(this);
    if (size == 1)
      label->setText(tr("STR").arg(name));
    else
      label->setText(tr("STR").arg(QString::number(size)));
    
    lbl_warn->setPixmap(GuiIconProvider::instance()->getIcon("STR").pixmap(lbl_warn->height()));
    lbl_warn->setFixedWidth(lbl_warn->height());
    rememberBtn->setIcon(GuiIconProvider::instance()->getIcon("STR"));

    move(Utils::Misc::screenCenter(this));
    checkPermDelete->setChecked(defaultDeleteFiles || Preferences::instance()->deleteTorrentFilesAsDefault());
    connect(checkPermDelete, SIGNAL(clicked()), this, SLOT(updateRememberButtonState()));
    buttonBox->button(QDialogButtonBox::Cancel)->setFocus();
  }