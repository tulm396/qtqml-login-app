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
                    text: qsTr("This is ToolBar");
                }
                ToolButton {
                    id: toolButtonLogout;
                    visible: false;
                    text: qsTr("Logout");
                    onClicked: {
                        idMainController.userLogout();
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

    BlankPage {
        id: idPageBlank;
    }

    StackView {
        id: idStackView;
        anchors.fill: parent;
        initialItem: idPageBlank;
    }

    MainController {
        id: idMainController;
    }

    Component.onCompleted: {
        setX(Screen.width / 2 - width / 2);
        setY(Screen.height / 2 - height / 2);

        if (idMainController.isUserLoggedIn()) {
            idStackView.push(idPageProfile);
            toolButtonLogout.visible = !toolButtonLogout.visible;
        } else {
            idStackView.push(idPageLogin);
        }
    }

    Connections {
        target: idMainController;

        onLogout: {
            toolButtonLogout.visible = !toolButtonLogout.visible;
            idStackView.pop();
            idStackView.push(idPageLogin);
        }
    }

}
