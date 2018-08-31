import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    property var lastReplay
    Component.onCompleted: {
        myFirebase.getValue()
    }

    Connections{
        target: myFirebase

        onEventResponseReady:{
            console.log("myFirebase.getPath(): "+ myFirebase.getPath())
            console.log("replyData: "+ replyData)
            console.log("replyJSON: "+ replyJSON.nom)
            lastReplay = replyJSON
        }

        onEventDataChanged:{
            console.log("myFirebase.getPath(): "+ myFirebase.getPath())
            console.log("changedData: "+ changedData)
        }
    }

    MouseArea{
        anchors.fill: parent
        onClicked: {
            lastReplay.nom = "cccc"
            myFirebase.setValue(lastReplay)
        }
    }
}
