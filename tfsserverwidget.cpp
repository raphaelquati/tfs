#include "tfsserverwidget.h"
#include "ui_tfsserverwidget.h"

namespace Tfs {
namespace Internal {

TfsServerWidget::TfsServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TfsServerWidget)
{
    ui->setupUi(this);
    setMinimumWidth(500);
    setMinimumHeight(400);
}


void TfsServerWidget::restoreSettings(const QString &group, const QSettings *s)
{
    const QChar separator = QLatin1Char('|');
    const QStringList hosts = s->value(group + QLatin1Char('/') + QLatin1String("servers"), QStringList()).toStringList();
    foreach (const QString &h, hosts) {
        const int sepPos = h.indexOf(separator);
        //if (sepPos == -1)
            //addHost(GitoriousHost(h));
        //else
            //addHost(GitoriousHost(h.mid(0, sepPos), h.mid(sepPos + 1)));
    }
}

} // namespace Internal
} // namespace Tfs
