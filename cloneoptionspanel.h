#ifndef CLONEOPTIONSPANEL_H
#define CLONEOPTIONSPANEL_H

#include <QWidget>

namespace Tfs {
namespace Internal {

namespace Ui {
class CloneOptionsPanel;
}

class CloneOptionsPanel : public QWidget
{
    Q_OBJECT

public:
    explicit CloneOptionsPanel(QWidget *parent = 0);
    ~CloneOptionsPanel();

    bool useAuthentication() const;
    QString authUsername() const;
    QString authPassword() const;

private:
    Ui::CloneOptionsPanel *ui;
};

} // namespace Internal
} // namespace Tfs

#endif // CLONEOPTIONSPANEL_H

