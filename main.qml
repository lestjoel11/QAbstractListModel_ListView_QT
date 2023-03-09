import QtQuick 2.15
import QtQuick.Window 2.15
import UserInfo
Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    ListView{

        anchors.fill: parent
        clip:true
        model: UserDetail{}
        MouseArea{
            anchors.fill: parent
            onClicked: {
                console.log()
            }
    }
        delegate: Text {

            id: name
            text: model.name

        }
    }
}
