#include "cloneoptionspanel.h"
#include "ui_cloneoptionspanel.h"

using namespace Tfs::Internal;

CloneOptionsPanel::CloneOptionsPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CloneOptionsPanel)
{
    ui->setupUi(this);
}

CloneOptionsPanel::~CloneOptionsPanel()
{
    delete ui;
}


bool Tfs::Internal::CloneOptionsPanel::useAuthentication() const
{
    return ui->authentication->isChecked();
}

QString Tfs::Internal::CloneOptionsPanel::authUsername() const
{
    return ui->username->text();
}

QString Tfs::Internal::CloneOptionsPanel::authPassword() const
{
    return ui->password->text();
}
