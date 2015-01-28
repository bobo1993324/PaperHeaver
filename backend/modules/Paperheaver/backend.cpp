#include <QtQml>
#include <QtQml/QQmlContext>
#include "backend.h"
#include "filemodel.h"
#include "googledrivemodel.h"
#include "mytype.h"


void BackendPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("Paperheaver"));

    qmlRegisterType<MyType>(uri, 1, 0, "MyType");
    qmlRegisterType<PageHeaver::GoogleDriveModel>(uri, 1, 0, "GoogleDriveModel");
    qmlRegisterType<PageHeaver::FileModel>(uri, 1, 0, "FileModel");
}

void BackendPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    QQmlExtensionPlugin::initializeEngine(engine, uri);
}

