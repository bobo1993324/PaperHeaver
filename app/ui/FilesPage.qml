import QtQuick 2.2
import Ubuntu.Components 1.1
import Ubuntu.Components.Popups 1.0
import "../components"
Page {
    title: i18n.tr("Recent Files")
    head {
        actions:[
            Action {
                iconName: "add"
                text: i18n.tr("Open file")
                onTriggered: {
                    PopupUtils.open(Qt.resolvedUrl("../components/ContentPickerDialog.qml"))
                }
            }
        ]
    }
    ContentPickerDialog {}

    EmptyState {
        id: emptyState
        title: i18n.tr("No Google account linked");
        anchors.centerIn: parent
        visible: settings.accessToken.length == 0
    }
    Button {
        text: i18n.tr("Link Google account")
        anchors {
            top: emptyState.bottom
            topMargin: units.gu(1)
            horizontalCenter: emptyState.horizontalCenter
        }
        visible: emptyState.visible
        onTriggered: {
            var url = googleDriveModel.getAuthenticationRquestURL(
                        "https://www.googleapis.com/auth/drive.file");
            var loginPage = pageStack.push(
                        Qt.resolvedUrl("./LoginPage.qml"), {"url": url});
        }
    }
}
