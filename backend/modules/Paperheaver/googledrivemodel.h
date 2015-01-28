#ifndef GOOGLEDRIVEMODEL_H
#define GOOGLEDRIVEMODEL_H

#include <QList>
#include <QAbstractItemModel>
#include <QNetworkAccessManager>
#include <QSettings>
#include <QHash>
#include "filetreeitem.h"

namespace PageHeaver {

class GoogleDriveModel : public QAbstractItemModel
{
    Q_OBJECT

    Q_PROPERTY(QString authorizationCode WRITE setAuthorizationCode)
    Q_PROPERTY(QString clientId WRITE setClientId)
    Q_PROPERTY(QString clientSecret WRITE setClientSecret)
    Q_PROPERTY(QString redirectUri WRITE setRedirectUri)
    Q_PROPERTY(QString accessToken READ accessToken WRITE setAccessToken NOTIFY accessTokenChanged)
    Q_PROPERTY(QString refreshToken READ refreshToken WRITE setRefreshToken NOTIFY refreshTokenChanged)

    enum {
        RoleFileTitle = Qt::UserRole + 1,
        RoleFileMimeType,
        RoleFileAlternateLink
    };
public:
    explicit GoogleDriveModel(QObject *parent = 0);
    ~GoogleDriveModel();

    Q_INVOKABLE QString getAuthenticationRquestURL(QString scope);

    virtual QModelIndex index(int row, int column,
                              const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &child) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QHash<int,QByteArray> roleNames() const;

    QModelIndex index(FileTreeItem *item);

    void setAuthorizationCode(QString code);
    void setClientId(QString clientId);
    void setClientSecret(QString clientSecret);
    void setRedirectUri(QString redirectUri);
    void setAccessToken(QString accessToken);
    void setRefreshToken(QString refreshToken);

    QString accessToken();
    QString refreshToken();

    Q_INVOKABLE void requestRefreshToken();
    Q_INVOKABLE void requestUploadFile(QString localFileUrl);
signals:

    void accessTokenChanged();
    void getNewAccessToken();
    void refreshTokenChanged();
    void credentialExpired();

public slots:

    void networkReplyFinished(QNetworkReply *);
    void handleAccessTokenChanged();

private:
    void requestAccessToken(QString code);
    void requestListChildren(QString parentName);

    QNetworkAccessManager conManager;
    QString m_clientId;
    QString m_clientSecret;
    QString m_redirectUri;
    QString m_accessToken;
    QString m_refreshToken;
    QHash<QString, FileTreeItem *> m_fileTreeMap; // parentId,

};

}

#endif // GOOGLEDRIVEMODEL_H
