#ifndef TFSSERVERWIZARDPAGE_H
#define TFSSERVERWIZARDPAGE_H

#include "tfsserverwidget.h"

#include <QWizardPage>

namespace Tfs {
namespace Internal {

class TfsServerWizardPage : public QWizardPage
{
    Q_OBJECT
public:
    explicit TfsServerWizardPage(QWidget *parent = 0);
    ~TfsServerWizardPage() { };

signals:

public slots:

private:
    TfsServerWidget *m_widget;

};

} // namespace Internal
} // namespace Tfs

#endif // TFSSERVERWIZARDPAGE_H
