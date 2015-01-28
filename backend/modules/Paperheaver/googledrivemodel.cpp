#include "googledrivemodel.h"
#include <cassert>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>

namespace PageHeaver {

GoogleDriveModel::GoogleDriveModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    connect(&conManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(networkReplyFinished(QNetworkReply*)));
    connect(this, SIGNAL(accessTokenChanged()), this, SLOT(handleAccessTokenChanged()));
}

GoogleDriveModel::~GoogleDriveModel()
{

}

QString GoogleDriveModel::getAuthenticationRquestURL(QString scope)
{
    return QString("https://accounts.google.com/o/oauth2/auth?response_type=")
                + "code"
            + "&client_id="
                + m_clientId
            + "&redirect_uri="
                + m_redirectUri
            + "&scope="
            + scope;
}

QModelIndex GoogleDriveModel::index(int row, int column, const QModelIndex &parent) const
{

}

QModelIndex GoogleDriveModel::parent(const QModelIndex &child) const
{

}

int GoogleDriveModel::rowCount(const QModelIndex &parent) const
{

}

int GoogleDriveModel::columnCount(const QModelIndex &parent) const
{

}

QVariant GoogleDriveModel::data(const QModelIndex &index, int role) const
{

}

void GoogleDriveModel::requestAccessToken(QString code)
{
    QUrl url;
    url.setScheme("https");
    url.setHost("www.googleapis.com");
    url.setPath("/oauth2/v3/token");
    QUrlQuery query;
    query.addQueryItem("code", code);
    query.addQueryItem("client_id", m_clientId);
    query.addQueryItem("client_secret", m_clientSecret);
    query.addQueryItem("redirect_uri", m_redirectUri);
    query.addQueryItem("grant_type", "authorization_code");
    url.setQuery(query);
    QString dataString = url.toString(QUrl::RemoveScheme|QUrl::RemoveAuthority|
                                      QUrl::RemovePath).mid(1);
    QByteArray postData;
    postData.append(dataString.toUtf8());
    QUrl xQuery(url.toString(QUrl::RemoveQuery));

    QNetworkRequest rq(xQuery);
    conManager.post(rq, postData);
}

void GoogleDriveModel::setAuthorizationCode(QString code)
{
    qDebug() << "GoogleDriveModel::setAuthorizationCode";
    // Get access token
    requestAccessToken(code);
}

void GoogleDriveModel::setClientId(QString clientId)
{
    m_clientId = clientId;
}

void GoogleDriveModel::setClientSecret(QString clientSecret)
{
    m_clientSecret = clientSecret;
}

void GoogleDriveModel::setRedirectUri(QString redirectUri)
{
    m_redirectUri = redirectUri;
}

void GoogleDriveModel::setAccessToken(QString accessToken)
{
    if (m_accessToken != accessToken) {
        m_accessToken = accessToken;
        emit accessTokenChanged();
    }
}

void GoogleDriveModel::setRefreshToken(QString refreshToken)
{
    m_refreshToken = refreshToken;
    emit refreshTokenChanged();
}

QString GoogleDriveModel::accessToken()
{
    return m_accessToken;
}

QString GoogleDriveModel::refreshToken()
{
    return m_refreshToken;
}

void GoogleDriveModel::networkReplyFinished(QNetworkReply * reply)
{
    if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 401) {
        //invalid credential
        emit credentialExpired();
        return;
    }
    qDebug() << "GoogleDriveModel::networkReplyFinished"
                << reply->url()
                   << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    QString response(reply->readAll());
    qDebug() << response;
    QJsonDocument doc = QJsonDocument::fromJson(response.toLatin1());
    assert(doc.isObject());
    QJsonObject object = doc.object();
    if (reply->url().toString().contains("/oauth2/v3/token")) {
        //Get token
        setAccessToken(object["access_token"].toString());
        setRefreshToken(object["refresh_token"].toString());
        emit getNewAccessToken();
    } else if (object["kind"].toString() == "drive#childList") {
        qDebug() << "TODO handle child list";
    }
}

void GoogleDriveModel::handleAccessTokenChanged()
{
    assert(!m_accessToken.isEmpty());
    //have a valid access Token now, list all files
    requestListChildren("root");
}

void GoogleDriveModel::requestListChildren(QString parentName)
{
    QUrl url;
    url.setScheme("https");
    url.setHost("www.googleapis.com");
    url.setPath(QString("/drive/v2/files/%1/children").arg(parentName));
    QUrlQuery query;
    query.addQueryItem("key", m_clientId);
    url.setQuery(query);
    QNetworkRequest rq(url);
    rq.setRawHeader(QByteArray("Authorization"), ("Bearer " + m_accessToken).toLocal8Bit());
    conManager.get(rq);
}

void GoogleDriveModel::requestRefreshToken()
{
    qDebug() << "GoogleDriveModel::requestRefreshToken";
}

}
