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
                target: detailsColumn;
            }
            PropertyChanges {
                target: moreDetails
                visible: false

            }
        },
        //Question?: HOw to make column dynamic to the size of the text inside it?
        State {
            name: "expanded"
            PropertyChanges {
                target: infoBox;
                color:"green"
                height: 145;
            }
            PropertyChanges {
                target: detailsColumn;
            }
            PropertyChanges {
                target: moreDetails
                visible: true

            }
        }
    ]
    state: "default"

    transitions: [
        Transition {
            from:"default"
            to: "expanded";
            PropertyAnimation {
                target: infoBox
                property: "height"
                duration: 130
            }

        },
        Transition {
            from: "expanded";
            to:"default"
            PropertyAnimation {
                target: moreDetails
                property: "visible"
                duration: 280
            }
            PropertyAnimation {
                target: infoBox
                property: "height"
                duration: 300
            }
        }
    ]

    border.color: color.lighter()
    Column{
        id:detailsColumn
        anchors.horizontalCenter: infoBox.horizontalCenter
        padding:5
        Text {
            id: name
            font:{
                font.bold=3;
            }
        }
        Item{
            id:moreDetails
            anchors.top: name.bottom
            x: balance.paintedWidth-detailsColumn.width

            Column{
                padding:7
                spacing:5
                id:moreDetailsColumn
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
    }


    MouseArea{
        anchors.fill: parent
        onClicked: function(){
            infoBox.state = (infoBox.state === "default"?"expanded":"default");
            console.log(phone.paintedHeight)
        }
    }

}

