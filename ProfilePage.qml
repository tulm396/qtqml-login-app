import QtQuick 2.0
import QtQuick.Controls 2.2

Page {
    id: profilePage;

    property int buttonWidth: 250;

    Rectangle {
        anchors.fill: parent;
        anchors.centerIn: parent;
        anchors.horizontalCenter: parent.horizontalCenter;
        Column {
            spacing: 16;
            anchors.centerIn: parent;

            Column {
                spacing: 4;
                anchors.horizontalCenter: parent.horizontalCenter;
                Label { id: labelUsername; text: " "; }
                Label { id: labelPassword; text: " "; }
            }

            Row {
                spacing: 16;
                anchors.horizontalCenter: parent.horizontalCenter;
                RoundButton {
                    id: roundButtonGetProfile;
                    width: buttonWidth;
                    text: "Get Your Profile";
                    smooth: true;
                    onClicked: {
                        console.log("Button Get Profile clicked.");
                    }
                }
                RoundButton {
                    id: roundButtonExit;
                    width: buttonWidth;
                    text: "Exit";
                    smooth: true;
                    onClicked: Qt.quit();
                }
            }
        }
    }
}
