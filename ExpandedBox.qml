import QtQuick 2.15

Rectangle {
    id: infoBox
    property alias name: name.text

    property alias age: age.text
    property alias balance: balance.text
    property alias email: email.text
    property alias phone: phone.text
    property alias gender: gender.text

    states: [
        State {
            name: "default"
            PropertyChanges {
                target: infoBox;
                color:"steelblue"
                height: 30;

            }
            PropertyChanges {
                target: name;
            }
        },
        State {
            name: "expanded"
            PropertyChanges {
                target: infoBox;
                color:"green"
                height: 70;
            }
            PropertyChanges {
                target: name;
                anchors.top: parent.top

            }
        }
    ]
    state: "default"

    transitions: [
        Transition {
            PropertyAnimation {
                target: infoBox
                property: "height"
                duration: 150
            }
            NumberAnimation {
                target: name
                property: "anchors"
                duration: 150
            }

        }
    ]

    border.color: color.lighter()
    width: parent.width
    Column{
        id:column
        spacing:5
        anchors.centerIn: parent
        Text {
            id: name
        }
        Item{
            id:moreDetails
            visible:false

            Text{
                id:balance

            }
            Text{
                id:age

            }
            Text{
                id:gender

            }
            Text{
                id:email

            }
            Text{
                id:phone

            }
        }
    }


    MouseArea{
        anchors.fill: parent
        onClicked: function(){
            infoBox.state = (infoBox.state === "default"?"expanded":"default");
        }
    }

}

