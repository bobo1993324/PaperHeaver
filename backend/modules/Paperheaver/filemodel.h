#ifndef FILEMODEL_H
#define FILEMODEL_H

#include <QAbstractProxyModel>
#include "filetreeitem.h"

namespace PageHeaver {

class FileModel : public QAbstractProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QAbstractItemModel * sourceModel READ sourceModel WRITE setSourceModel)

public:
    explicit FileModel(QObject *parent = 0);

    //QAbstractProxyModel
    virtual QModelIndex mapToSource(const QModelIndex &proxyIndex) const;
    virtual QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;
    virtual void setSourceModel(QAbstractItemModel *sourceModel);

    //QAbstractItemModel
    virtual QModelIndex index(int row, int column, const QModelIndex&parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex&) const;
    virtual int rowCount(const QModelIndex&) const;
    virtual int columnCount(const QModelIndex&) const;

signals:

public slots:
    void handleSourceRowInserted(QModelIndex parent, int first, int last);

private:
    FileTreeItem *m_currentFolder;
};

}
#endif // FILEMODEL_H
