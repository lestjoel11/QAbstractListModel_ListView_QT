import QtQuick 2.15
import QtQuick.Window 2.15
import UserInfo
Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    Text{
        id:title
        text: "List of Users"
        font: {
            font.bold = 1;
            font.letterSpacing = 2;
        }
    }
    ListView{

        anchors.fill: parent
        anchors.topMargin: 15
        clip:true
        model: UserDetail{}

        delegate:ExpandedBox
        {
            name: model.name
            age: model.age
            balance: model.balance
            gender: model.gender
            email: model.email
            phone: model.phone

        }
        spacing: 1
    }
}
