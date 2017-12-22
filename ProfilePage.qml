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
                Label { id: labelAddress; text: " "; }
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
                        idMainController.getUserProfile();
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

    // Create connections to signal from Main Controller
    Connections {
        target: idMainController;

        onGetProfile: {
            switch (flag) {
                case -1:
                    // For now, don't do anything more
                    break;
                case 0:
                    // Authorization failed
                    break;
                case 1:
                    // Request successfully and had data
                    labelUsername.text = qsTr("Username: %1.").arg(data["username"]);
                    labelAddress.text = qsTr("Address: %1.").arg(data["address"]);
                    break;
            }
        }
    }
}
