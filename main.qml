import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Window 2.2

import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls.Material 2.0

import MainController 1.0

ApplicationWindow {
    visible: true;
    width: 1024; minimumWidth: 1024;
    height: 600; minimumHeight: 600;
    title: qsTr("TuLM Login App");

    header: ToolBar {
        Rectangle {
            anchors.fill: parent;
            color: "lightgrey";

            RowLayout {
                anchors.fill: parent;
                Rectangle {
                    width: 20;
                    height: 0;
                }
                Label {
                    id: labelTitle;
                    horizontalAlignment: Qt.AlignLeft;
                    verticalAlignment: Qt.AlignVCenter;
                    Layout.fillWidth: true;
                    Layout.fillHeight: true;
                    text: qsTr("Welcome! This is Login page!");
                }
                ToolButton {
                    id: toolButtonLogout;
                    visible: false;
                    text: qsTr("Logout");
                    onClicked: {
                        labelTitle.text = qsTr("Welcome! This is Login page!");
                        idStackView.pop();
                    }
                }
            }
        }
    }

    LoginPage {
        id: idPageLogin;
    }

    ProfilePage {
        id: idPageProfile;
    }

    StackView {
        id: idStackView;
        anchors.fill: parent;
        initialItem: {
            if (!idMainController.isUserLoggedIn()) {
                idPageLogin;
            } else {
                idPageProfile;
            }
        }
    }

    MainController {
        id: idMainController;
    }

    Component.onCompleted: {
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);
    }

}
