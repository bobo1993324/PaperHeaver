#ifndef FILETREEITEM_H
#define FILETREEITEM_H

#include <QObject>

namespace PageHeaver {

class FileTreeItem : public QObject
{
    Q_OBJECT
public:
    explicit FileTreeItem(QObject *parent = 0, QString id = "", FileTreeItem *folder = 0);

    void addChild(FileTreeItem * child);
    FileTreeItem * getChild(int row);
    int childCount();

    FileTreeItem * getContainingFolder();

    QString getId();

    int indexOf(FileTreeItem *child);

    void setTitle(QString title) { m_title = title; }
    void setMimeType(QString mimeType) { m_mimeType = mimeType; }
    void setAlternateLink(QString alternateLink) { m_alternateLink = alternateLink; }

    QString title() { return m_title; }
    QString mimeType() { return m_mimeType; }
    QString alternateLink() { return m_alternateLink; }

signals:

public slots:

private:
    QString m_id;
    QList<FileTreeItem *> m_childList;
    FileTreeItem * m_folder;
    QString m_title;
    QString m_mimeType;
    QString m_alternateLink;
};

}

#endif // FILETREEITEM_H
