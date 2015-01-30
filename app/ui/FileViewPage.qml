import QtQuick 2.2
import Ubuntu.Components 1.1
import Ubuntu.Web 0.2

Page {
    property alias url: webview.url
    WebView {
        id: webview
        anchors.fill: parent
    }
}
