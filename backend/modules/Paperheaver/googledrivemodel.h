#ifndef GOOGLEDRIVEMODEL_H
#define GOOGLEDRIVEMODEL_H

#include <QAbstractItemModel>
#include <QNetworkAccessManager>
#include <QSettings>

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

    void setAuthorizationCode(QString code);
    void setClientId(QString clientId);
    void setClientSecret(QString clientSecret);
    void setRedirectUri(QString redirectUri);
    void setAccessToken(QString accessToken);
    void setRefreshToken(QString refreshToken);

    QString accessToken();
    QString refreshToken();

    void requestListChildren(QString parentName);
    Q_INVOKABLE void requestRefreshToken();
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

    QNetworkAccessManager conManager;
    QString m_clientId;
    QString m_clientSecret;
    QString m_redirectUri;
    QString m_accessToken;
    QString m_refreshToken;

};

}

#endif // GOOGLEDRIVEMODEL_H
