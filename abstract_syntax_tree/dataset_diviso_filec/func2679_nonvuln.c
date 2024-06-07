Smb4KMountDialog::Smb4KMountDialog( Smb4KShare *share, QWidget *parent )
: KDialog( parent ), m_share( share ), m_valid( true )
{
  setCaption( i18n( "STR" ) );
  setButtons( Ok | Cancel );
  setDefaultButton( Ok );

  setupView();

  connect( this, SIGNAL(okClicked()), SLOT(slotOkClicked()) );
  connect( this, SIGNAL(cancelClicked()), SLOT(slotCancelClicked()) );

  setMinimumWidth( sizeHint().width() > 350 ? sizeHint().width() : 350 );

  KConfigGroup group( Smb4KSettings::self()->config(), "STR" );
  restoreDialogSize( group );

  m_share_input->completionObject()->setItems( group.readEntry( "STR", QStringList() ) );
  m_ip_input->completionObject()->setItems( group.readEntry( "STR", QStringList() ) );
  m_workgroup_input->completionObject()->setItems( group.readEntry( "STR", QStringList() ) );
}