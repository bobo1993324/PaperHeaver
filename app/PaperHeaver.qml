import QtQuick 2.0
import Ubuntu.Components 1.1
import Paperheaver 1.0
import "ui"
import "components"

/*!
    \brief MainView with Tabs element.
           First Tab has a single Label and
           second Tab has a single ToolbarAction.
*/

MainView {
    id: pageHeaver
    // objectName for functional testing purposes (autopilot-qt5)
    objectName: "mainView"

    // Note! applicationName needs to match the "name" field of the click manifest
    applicationName: "com.ubuntu.developer.bobo1993324.paperheaver"

    /*
     This property enables the application to change orientation
     when the device is rotated. The default is false.
    */
    //automaticOrientation: true

    // Removes the old toolbar and enables new features of the new header.
    useDeprecatedToolbar: false

    width: units.gu(100)
    height: units.gu(75)

    PageStack {
        id: pageStack
        Component.onCompleted: {
            push(Qt.resolvedUrl("./ui/FilesPage.qml"))
        }
    }

    GoogleDriveModel {
        id: googleDriveModel
        clientId: "68272877916-b4rvbf5e8a064hast9qpgg7329lepeqq.apps.googleusercontent.com"
        clientSecret: "ztxsRehxDidI3u1wA6MBAr6q"
        redirectUri: "http://localhost"
        onGetNewAccessToken: {
            console.log("get new access token", accessToken)
            settings.storeAccessToken(accessToken);
        }
        onCredentialExpired: {
            if (settings.refreshToken.length > 0) {
                refreshToken = settings.refreshToken;
                requestRefreshToken();
            } else {
                settings.clear()
            }
        }
    }

    Settings {
        id: settings
        onAccessTokenChanged: {
            if (accessToken.length > 0)
                googleDriveModel.accessToken = accessToken
        }
    }
}

