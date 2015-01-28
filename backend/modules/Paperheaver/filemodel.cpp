#include "filemodel.h"

#include <cassert>
#include "filetreeitem.h"
#include "googledrivemodel.h"

namespace PageHeaver {

FileModel::FileModel(QObject *parent) :
    QAbstractProxyModel(parent), m_currentFolder(0)
{
}

QModelIndex FileModel::mapToSource(const QModelIndex &proxyIndex) const
{
    GoogleDriveModel *model = qobject_cast<GoogleDriveModel *>(sourceModel());
    if (proxyIndex.isValid()) {
        FileTreeItem *realItem = static_cast<FileTreeItem *>(proxyIndex.internalPointer());
        return model->index(realItem);
    } else {
        return model->index(0, 0, QModelIndex());
    }
}

QModelIndex FileModel::mapFromSource(const QModelIndex &sourceIndex) const
{
    FileTreeItem *realItem = static_cast<FileTreeItem *>(sourceIndex.internalPointer());
    if (m_currentFolder != realItem->getContainingFolder()) {
        return QModelIndex();
    }
    return index(realItem->getContainingFolder()->indexOf(realItem), 0);
}

void FileModel::setSourceModel(QAbstractItemModel *sourceModel)
{
    QAbstractProxyModel::setSourceModel(sourceModel);
    m_currentFolder = static_cast<FileTreeItem *>(qobject_cast<GoogleDriveModel *>(sourceModel)->index(0, 0, QModelIndex()).internalPointer());
    connect(sourceModel, SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(handleSourceRowInserted(QModelIndex, int, int)));
}

QModelIndex FileModel::index(int row, int column, const QModelIndex &parent) const
{
    assert(!parent.isValid());
    return createIndex(row, column, m_currentFolder->getChild(row));
}

QModelIndex FileModel::parent(const QModelIndex &) const
{
    return QModelIndex();
}

int FileModel::rowCount(const QModelIndex &parent) const
{
    qDebug() << "FileModel::rowCount" << m_currentFolder->childCount();
    return m_currentFolder->childCount();
}

int FileModel::columnCount(const QModelIndex &) const
{
    return 1;
}

void FileModel::handleSourceRowInserted(QModelIndex parent, int first, int last)
{
    qDebug() << "FileModel::handleSourceRowInserted" << first << last;
    if (parent.internalPointer() == m_currentFolder) {
        beginInsertRows(QModelIndex(), first, last);
        endInsertRows();
    }
}

}
