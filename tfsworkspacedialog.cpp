#include "tfsworkspacedialog.h"
#include "ui_tfsworkspacedialog.h"
#include <QDomDocument>
#include <QHostInfo>
#include <QDebug>


#include "tfsworkspacedialogedit.h"

namespace Tfs {
namespace Internal {


TfsWorkspaceDialog::TfsWorkspaceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TfsWorkspaceDialog)
{
    ui->setupUi(this);
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(&model);
    ui->tableView->setModel(proxyModel);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui->checkBox, SIGNAL(stateChanged(int)), this, SLOT(stateChanged(int)));
    connect(ui->cmdEdit, SIGNAL(clicked()), this, SLOT(editWorkspace()));


    this->setCursor(Qt::WaitCursor);
    connect(TfsPlugin::instance()->client(), SIGNAL(parseWorkspaceOutput(QString)), this, SLOT(parse(QString)));

    TfsPlugin::instance()->client()->listWorkspaces();
}

TfsWorkspaceDialog::~TfsWorkspaceDialog()
{
    delete ui;
}

void TfsWorkspaceDialog::parse(const QString &text)
{
    QList<TfsWorkspace *> list;

    QDomDocument doc;
    doc.setContent(text);

    QDomElement docElem = doc.documentElement();
    QDomNode n = docElem.firstChild();
    QDomNode n2;
    while(!n.isNull()) {

        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            if (e.tagName() == QLatin1String("workspace")) {
                TfsWorkspace *workspace = new TfsWorkspace();
                workspace->setName(e.attribute(QLatin1String("name")));
                workspace->setOwner(e.attribute(QLatin1String("owner")));
                workspace->setComputer(e.attribute(QLatin1String("computer")));
                workspace->setComment(e.attribute(QLatin1String("comment")));
                //workspace->setServer(e.attribute(QLatin1String("server")));
                workspace->setServer(QLatin1String("server"));

                list.append(workspace);

                if (n.hasChildNodes()) {
                    //WorkFolders
                    QDomNodeList childs = n.childNodes();

                    for (int i = 0; i < childs.count(); i++) {
                        n2 = childs.at(i);
                        QDomElement el = n2.toElement();
                        if (el.tagName() == QLatin1String("working-folder")) {
                            TfsWorkFolder *wf = new TfsWorkFolder();

                            //el.attribute(QLatin1String("server-item"));
                            //el.attribute(QLatin1String("local-item"));
                            //el.attribute(QLatin1String("type"));
                            //el.attribute(QLatin1String("depth"));
                        }
                    }
                }
            }
        }
        n = n.nextSibling();
    }

    model.setModelData(list);

    ui->tableView->resizeColumnsToContents();

    QMetaObject::invokeMethod(this, "resetCursor");
}

void TfsWorkspaceDialog::resetCursor()
{
    this->setCursor(Qt::ArrowCursor);
}

void TfsWorkspaceDialog::stateChanged(int state)
{
    proxyModel->setFilterKeyColumn(1);
    if (state == Qt::Checked) {
        proxyModel->setFilterFixedString(QLatin1String(""));
    } else {
        proxyModel->setFilterFixedString(QHostInfo::localHostName());
    }

}

void TfsWorkspaceDialog::editWorkspace()
{
    QModelIndex index = ui->tableView->selectionModel()->selectedRows().first();

    TfsWorkspace *workspace = model.getTfsWorkspace(index);

    TfsWorkspaceDialogEdit edit(this, workspace);
    edit.show();

    if (edit.Accepted) {

    }
}


} // namespace Internal
} // namespace Tfs
