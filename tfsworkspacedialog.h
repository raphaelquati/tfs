#ifndef TFSWORKSPACEDIALOG_H
#define TFSWORKSPACEDIALOG_H

#include <QDialog>
#include <QAbstractTableModel>
#include <QSortFilterProxyModel>

#include "tfsdatatypes.h"
#include "tfsplugin.h"
#include "tfsworkspacemodel.h"

namespace Tfs {
namespace Internal {

namespace Ui {
class TfsWorkspaceDialog;
}

class TfsWorkspaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TfsWorkspaceDialog(QWidget *parent = 0);
    ~TfsWorkspaceDialog();

private:
    Ui::TfsWorkspaceDialog *ui;

    TfsWorkspaceModel model;
    QSortFilterProxyModel *proxyModel;

    void resetCursor();

public slots:
    void stateChanged(int state);
    void editWorkspace();

    virtual void parse(const QString &text);
};

} // namespace Internal
} // namespace Tfs

#endif // TFSWORKSPACEDIALOG_H
