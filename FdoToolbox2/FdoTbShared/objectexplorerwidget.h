#ifndef OBJECTEXPLORERWIDGET_H
#define OBJECTEXPLORERWIDGET_H

#include <QDockWidget>
#include "FdoTbShared_global.h"

namespace Ui {
class ObjectExplorerWidget;
}

class FDOTBSHAREDSHARED_EXPORT ObjectExplorerWidget : public QDockWidget
{
    Q_OBJECT
    
public:
    explicit ObjectExplorerWidget(QWidget *parent = 0);
    ~ObjectExplorerWidget();
    
private:
    Ui::ObjectExplorerWidget *ui;
};

#endif // OBJECTEXPLORERWIDGET_H
