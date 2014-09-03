#ifndef TFSSERVERWIDGET_H
#define TFSSERVERWIDGET_H

#include <QSettings>
#include <QWidget>


namespace Tfs {
namespace Internal {

namespace Ui { class TfsServerWidget; }


class TfsServerWidget : public QWidget
{
    Q_OBJECT
public:
    TfsServerWidget(QWidget *parent = 0);

    void restoreSettings(const QString &group, const QSettings *s);
signals:
    void validChanged();

public slots:

private:
    Ui::TfsServerWidget *ui;


};

} // namespace Internal
} // namespace Tfs

#endif // TFSSERVERWIDGET_H
