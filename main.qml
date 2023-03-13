import QtQuick 2.15
import QtQuick.Window 2.15
import UserInfo


//Implement a C++ method that accepts the items in array
Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("User Bank Details")
    Text{
        id:title
        text: "List of Users"
        padding: 5
        font{
            pixelSize:14;
            bold: true;
            letterSpacing: 2;
        }
        anchors.horizontalCenter: parent.horizontalCenter
    }
    ListView{
        anchors.fill: parent
        anchors.top: title.bottom
        anchors.topMargin: 30
        clip:true
        model: UserDetail{}

        delegate:ExpandedBox{
            width: root.width
            name: model.name
            age: "Age: " +model.age
            balance: "Balance: "+model.balance
            gender: "Gender: "+model.gender
            email: "Email: "+model.email
            phone: "Phone: "+model.phone

        }
        spacing: 1
    }


}
