#include "tfsserverwizardpage.h"

namespace Tfs {
namespace Internal {

#include <coreplugin/icore.h>

#include <QSettings>
#include <QVBoxLayout>

#include "tfsserverwidget.h"

static const char settingsGroupC[] = "Tfs";

static TfsServerWidget *createServerWidget()
{
//    const QSettings *settings = Core::ICore::settings();
//    const QString group = QLatin1String(settingsGroupC);


    //restoreSettings(group, settings);

    // Now create widget
    TfsServerWidget *rc = new TfsServerWidget;
//    rc->restoreSettings(group, settings);

    return rc;
}




TfsServerWizardPage::TfsServerWizardPage(QWidget *parent) :
    QWizardPage(parent),
    m_widget(createServerWidget())
{
    connect(m_widget, SIGNAL(validChanged()), this, SIGNAL(completeChanged()));
    QVBoxLayout *lt = new QVBoxLayout;
    lt->addWidget(m_widget);
    setLayout(lt);
    setTitle(tr("Host"));
    setSubTitle(tr("Select a host."));
}


} // namespace Internal
} // namespace Tfs
