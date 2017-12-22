import QtQuick 2.0
import QtQuick.Controls 2.2
Page {
    id: loginPage;

    //property alias labelWarningText: labelWarning.text;

    Rectangle {
        anchors.fill: parent;
        anchors.centerIn: parent;

        Column {
            spacing: 16;
            anchors.centerIn: parent;

            Column {
                spacing: 4;
                anchors.horizontalCenter: parent.horizontalCenter;

                Label {
                    id: labelWarning;
                    text: " ";
                    color: "red";
                    font.pixelSize: 9;
                }
            }

            Column {
                spacing: 4;
                anchors.horizontalCenter: parent.horizontalCenter;

                Label { text: "Username"; }

                TextField {
                    id: textFieldUsername;
                    width: 300;
                    text: "tulm";
                    placeholderText: "tulm";
                    focus: true;
                }
            }

            Column {
                spacing: 4;
                anchors.horizontalCenter: parent.horizontalCenter;

                Label { text: "Password"; }

                TextField {
                    id: textFieldPassword;
                    width: 300;
                    text: "leminhtu";
                    placeholderText: "leminhtu";
                    echoMode: "Password";
                }
            }

            Row {
                spacing: 16;
                anchors.horizontalCenter: parent.horizontalCenter;

                RoundButton {
                    id: roundButtonLogin;
                    text: "Login";
                    width: textFieldPassword.width / 2 - 8;
                    onClicked: {
                        if (textFieldUsername.text === "" || textFieldPassword.text === "") {
                            labelWarning.text = "* Username or Password cannot empty.";
                            return;
                        }
                        idMainController.userLogin(textFieldUsername.text, textFieldPassword.text);
                    }
                }

                RoundButton {
                    id: roundButtonExit;
                    text: "Exit";
                    width: roundButtonLogin.width;
                    onClicked: Qt.quit();
                }
            }
        }
    }

    Connections {
        target: idMainController;

        onLogin: {
            console.log(flag);
            console.log(message);

            if (flag === -1) {
                labelWarning.text = "* Cannot connect to service.";
                return;
            }

            if (flag === 1) {
                idStackView.push(idPageProfile);
                labelTitle.text = qsTr("Hello " + textFieldUsername.text);
                labelWarning.text = "* Succeed.";
            } else {
                labelWarning.text = "* Wrong Username or Password, try again.";
            }
        }
    }
}
