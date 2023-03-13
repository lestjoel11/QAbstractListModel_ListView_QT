import QtQuick 2.15

Rectangle {
    id: infoBox
    property alias name: name.text

    property alias age: age.text
    property alias balance: balance.text
    property alias email: email.text
    property alias phone: phone.text
    property alias gender: gender.text

    //Set height on info box and set it equal to column height
    border.color: color.lighter()
    states: [
        State {
            name: "default"
            PropertyChanges {
                target: infoBox;
                color:"darkgray"
                height: detailsColumn.height
//                height: 30;

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
                color:"cornsilk"
//                height: detailsColumn.height
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


    Column{
        id:detailsColumn
        anchors.horizontalCenter: infoBox.horizontalCenter
        padding:5
        Text {
            id: name
            font.bold:true;
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
        }
    }

}

