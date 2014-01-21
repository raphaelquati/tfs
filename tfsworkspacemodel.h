#ifndef TFSWORKSPACEMODEL_H
#define TFSWORKSPACEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include "tfsdatatypes.h"

namespace Tfs {
namespace Internal {



class TfsWorkspaceModel : public QAbstractTableModel {
    Q_OBJECT

private:
    QList<TfsWorkspace *> _model;

    // QAbstractItemModel interface
public:
    TfsWorkspaceModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void setModelData(const QList<TfsWorkspace *> &list);

    TfsWorkspace *getTfsWorkspace(const QModelIndex &index);
};

} // namespace Internal
} // namespace Tfs

#endif // TFSWORKSPACEMODEL_H
