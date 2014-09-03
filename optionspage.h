#ifndef OPTIONSPAGE_H
#define OPTIONSPAGE_H

#include "ui_optionpage.h"

#include <vcsbase/vcsbaseoptionspage.h>

#include <QWidget>
#include <QPointer>

namespace Tfs {
namespace Internal {

class TfsSettings;

class OptionsPageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OptionsPageWidget(QWidget *parent = 0);

    TfsSettings settings() const;
    void setSettings(const TfsSettings &s);
    QString searchKeywords() const;

private:
    Ui::OptionsPage m_ui;
};

class OptionsPage : public VcsBase::VcsBaseOptionsPage
{
    Q_OBJECT

public:
    OptionsPage();

    QWidget *widget();
    void apply();
    void finish();
//    bool matches(const QString &s) const;

signals:
    void settingsChanged();

private:
    QString m_searchKeywords;
    QPointer<OptionsPageWidget> optionsPageWidget;
};

} // namespace Internal
} // namespace Mercurial


#endif // OPTIONSPAGE_H








