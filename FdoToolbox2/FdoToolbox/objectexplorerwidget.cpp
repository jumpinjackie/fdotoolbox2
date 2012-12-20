#include "objectexplorerwidget.h"
#include "ui_objectexplorerwidget.h"

ObjectExplorerWidget::ObjectExplorerWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::ObjectExplorerWidget)
{
    ui->setupUi(this);
}

ObjectExplorerWidget::~ObjectExplorerWidget()
{
    delete ui;
}
