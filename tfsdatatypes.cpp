#include "tfsdatatypes.h"

namespace Tfs {
namespace Internal {

TfsWorkFolder::TfsWorkFolder()
{

}

TfsWorkFolder::~TfsWorkFolder()
{

}

TfsWorkspace::TfsWorkspace(TfsWorkspace *workspace)
    : QObject(workspace)
{

}

const QList<TfsWorkFolder *> TfsWorkspace::workfolders() const
{
    return m_workfolders;
}



} // namespace Internal
} // namespace Tfs
