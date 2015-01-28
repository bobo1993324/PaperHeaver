import QtQuick 2.2
import Ubuntu.Components 1.1
import U1db 1.0

Item {
    id: root
    property string accessToken
    property string refreshToken
    signal noAccessTokenStored()

    function storeAccessToken(accessToken) {
        root.accessToken = accessToken;
        console.log(aDatabase.listDocs().length);
        var tmp = {};
        tmp = aDocument.contents;
        console.log("contents ", tmp);
        tmp.accessToken = accessToken;
        aDocument.contents = tmp;
    }

    function clear() {
        aDocument.contents = {};
        accessToken = ""
    }

    Database {
        id: aDatabase
        path: "settings_db"
    }

    Document {
        id: aDocument
        database: aDatabase
        docId: 'settings_doc'
        create: true
        defaults: {
            "accessToken": "",
            "refreshToken": ""
        }
    }
    Component.onCompleted: {
        if (aDocument.contents.refreshToken)
            refreshToken = aDocument.contents.refreshToken;
        if (aDocument.contents.accessToken && aDocument.contents.accessToken.length > 0) {
            accessToken = aDocument.contents.accessToken;
        } else {
            noAccessTokenStored()
        }
    }
}
