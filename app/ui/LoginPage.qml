import QtQuick 2.2
import Ubuntu.Components 1.1
import Ubuntu.Web 0.2

Page {

    property alias url: webview.url

    signal getAutorizationCode(string code)

    title: i18n.tr("Login")

    WebView {
        id: webview
        anchors.fill: parent
        onUrlChanged: {
            console.log("Url changed to ", url);
            var urlInString = url.toString();
            if (urlInString.indexOf("?code=") >= 0) {
                var authorizationCode = urlInString.substr(urlInString.indexOf("=")+ 1);
                console.log("Get authorization code", authorizationCode);
                googleDriveModel.authorizationCode = authorizationCode;
                pageStack.pop();
            }
        }
    }
}
