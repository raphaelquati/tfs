#ifndef TFSWORKSPACEDIALOGEDIT_H
#define TFSWORKSPACEDIALOGEDIT_H

#include <QDialog>
#include  "tfsdatatypes.h"

namespace Tfs {
namespace Internal {

namespace Ui {
class TfsWorkspaceDialogEdit;
}

class TfsWorkspaceDialogEdit : public QDialog
{
    Q_OBJECT

public:
    explicit TfsWorkspaceDialogEdit(QWidget *parent = 0, TfsWorkspace *workspace = 0);
    ~TfsWorkspaceDialogEdit();
private slots:
    void showAdvanced();

private:
    Ui::TfsWorkspaceDialogEdit *ui;
};

} // namespace Internal
} // namespace Tfs

#endif // TFSWORKSPACEDIALOGEDIT_H
