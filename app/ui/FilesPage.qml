import QtQuick 2.2
import Ubuntu.Components 1.1
import Ubuntu.Components.Popups 1.0
import Ubuntu.Components.ListItems 1.0 as ListItem
import Paperheaver 1.0
import "../components"
Page {
    title: i18n.tr("Recent Files")
    head {
        actions:[
            Action {
                iconName: "add"
                text: i18n.tr("Open file")
                onTriggered: {
                    var picker = PopupUtils.open(Qt.resolvedUrl("../components/ContentPickerDialog.qml"))
                    picker.transferComplete.connect(function(items) {
                        //TODO read url from item

                    });
                    //TOOD move to top block
                    var url = "file:///home/luke/Documents/school/373/HW1-b.pdf";
                    googleDriveModel.requestUploadFile(url);
                }
            }
        ]
    }
    FileModel {
        id: fileModel
        sourceModel: googleDriveModel
    }
    ListView {
        anchors.fill: parent
        model: fileModel
        delegate: ListItem.Standard {
            text: title
            onClicked: {
                pageStack.push(Qt.resolvedUrl("./FileViewPage.qml"),
                               {
                                    title: title,
                                    url: alternateLink
                               })
            }
        }
    }

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
                        "https://www.googleapis.com/auth/drive");
            var loginPage = pageStack.push(
                        Qt.resolvedUrl("./LoginPage.qml"), {"url": url});
        }
    }
}
