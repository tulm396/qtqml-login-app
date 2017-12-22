import QtQuick 2.0
import QtQuick.Controls 2.2
Page {
    id: loginPage;

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
                        // Check input data
                        if (textFieldUsername.text === "" || textFieldPassword.text === "") {
                            labelWarning.text = "* Username or Password cannot empty.";
                            return;
                        }

                        // Call user log in
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

    onVisibleChanged: {
        toolButtonLogout.visible = !visible;
        labelWarning.text = " ";
        textFieldUsername.clear();
        textFieldPassword.clear();
    }

    Connections {
        target: idMainController;

        onLogin: {
            console.log("onLogin: flag " + flag + ", message: " + message);
            switch (flag) {
                case -1:
                    labelWarning.text = "* Cannot connect to service.";
                    break;
                case 0:
                    labelWarning.text = "* Wrong Username or Password, try again.";
                    break;
                case 1:
                    idStackView.push(idPageProfile);
                    labelTitle.text = qsTr("Hello %1! This is your page!").arg(textFieldUsername.text);
                    break;
            }
        }
    }
}
