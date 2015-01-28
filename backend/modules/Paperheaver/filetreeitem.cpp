#include "filetreeitem.h"
#include <cassert>

namespace PageHeaver {

FileTreeItem::FileTreeItem(QObject *parent, QString id, FileTreeItem *folder)
    : QObject(parent), m_id(id), m_folder(folder)
{

}

void FileTreeItem::addChild(FileTreeItem *child)
{
    m_childList.append(child);
}

FileTreeItem *FileTreeItem::getChild(int row)
{
    assert(row < m_childList.size());
    return m_childList[row];
}

int FileTreeItem::childCount()
{
    return m_childList.size();
}

FileTreeItem *FileTreeItem::getContainingFolder()
{
    return m_folder;
}

QString FileTreeItem::getId()
{
    return m_id;
}

int FileTreeItem::indexOf(FileTreeItem *child)
{
    return m_childList.indexOf(child);
}

}
