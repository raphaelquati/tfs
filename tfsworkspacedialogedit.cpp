#include "tfsworkspacedialogedit.h"
#include "ui_tfsworkspacedialogedit.h"

namespace Tfs {
namespace Internal {

TfsWorkspaceDialogEdit::TfsWorkspaceDialogEdit(QWidget *parent, TfsWorkspace *workspace) :
    QDialog(parent),
    ui(new Ui::TfsWorkspaceDialogEdit)
{
    ui->setupUi(this);
    ui->layoutAdvanced->widget()->setVisible(false);

    connect(ui->cmdAdvanced, SIGNAL(clicked()), this, SLOT(showAdvanced()));

    ui->txtName->setText(workspace->Name());
    ui->txtServer->setText(workspace->Server());
    ui->txtOwner->setText(workspace->Owner());
    ui->txtComputer->setText(workspace->Computer());
    ui->txtComment->setPlainText(workspace->Comment());
}

TfsWorkspaceDialogEdit::~TfsWorkspaceDialogEdit()
{
    delete ui;
}

void TfsWorkspaceDialogEdit::showAdvanced()
{
    QWidget *w = ui->layoutAdvanced->widget();

    if (w->isVisible()) {
        w->setVisible(false);
        ui->cmdAdvanced->setText(tr("Advanced >>"));
    } else {
        w->setVisible(true);
        ui->cmdAdvanced->setText(tr("<< Advanced"));
    }
}

} // namespace Internal
} // namespace Tfs
