#include "tfsworkspacemodel.h"

namespace Tfs {
namespace Internal {

TfsWorkspaceModel::TfsWorkspaceModel(QObject *parent)
    : QAbstractTableModel(parent) {

}

int TfsWorkspaceModel::rowCount(const QModelIndex &parent) const
{
    return _model.count();
}

int TfsWorkspaceModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant TfsWorkspaceModel::data(const QModelIndex &index, int role) const
{
    TfsWorkspace *d;
    d = _model.at(index.row());

    if (role == Qt::DisplayRole) {
        if (index.column() == 0)  {
            return d->Name();
        }

        if (index.column() == 1) {
            return  d->Computer();
        }

        if (index.column() == 2) {
            return d->Owner();
        }

        if (index.column() == 3) {
            return d->Comment();
        }
    }

    return QVariant();

}

QVariant TfsWorkspaceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
       if (section == 0) {
            return QLatin1String("Name");
       }

       if (section == 1) {
           return QLatin1String("Computer");
       }

       if (section == 2) {
           return QLatin1String("Owner");
       }

       if (section == 3) {
           return QLatin1String("Comment");
       }
   }

   return QVariant();
}

void TfsWorkspaceModel::setModelData(const QList<TfsWorkspace *> &list)
{
    beginResetModel();
    _model = list;
    endResetModel();
}

TfsWorkspace* TfsWorkspaceModel::getTfsWorkspace(const QModelIndex &index)
{
    return _model.at(index.row());
}

} // namespace Internal
} // namespace Tfs
