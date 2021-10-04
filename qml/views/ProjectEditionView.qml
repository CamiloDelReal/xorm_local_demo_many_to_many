import QtQuick
import QtQuick.Controls
import QtQuick.Controls.impl
import QtQuick.Controls.Material
import QtQuick.Layouts

import XApps.XOrmDemoManyToMany

import "qrc:/qml"
import "qrc:/qml/delegates"

XPane {
    id: projectEditionView

    property var listingListener: sharedData

    property var selectedIndexes: []

    Component.onCompleted: {
        viewModel.readMembers()
    }

    ProjectEditionViewModel {
        id: viewModel

        onProjectCreated: {
            listingListener.update()
            projectNavController.goBack()
        }
    }

    XScrollView {
        id: scrollview
        anchors.fill: parent
        ScrollIndicator.vertical: ScrollIndicator {}

        ColumnLayout {
            id: layout
            width: scrollview.contentView.availableWidth
            spacing: 12

            XHeadlineLabel {
                Layout.fillWidth: true
                text: qsTr("New project")
            }

            XFormTextField {
                id: txfName
                placeholderText: qsTr("Name")
                font.pixelSize: 18
                Layout.fillWidth: true
                Layout.topMargin: 12
            }

            XFormTextField {
                id: txfDescription
                placeholderText: qsTr("Description")
                wrapMode: TextArea.Wrap
                font.pixelSize: 14
                Layout.fillWidth: true
            }

            XTitleLabel {
                Layout.fillWidth: true
                Layout.topMargin: 16
                text: qsTr("Members")
            }

            XBodyLabel1 {
                text: qsTr("No members defined, for create a new project is required to have members in the system")
                wrapMode: Label.WordWrap
                horizontalAlignment: Label.AlignHCenter
                color: Material.color(Material.Red)
                Layout.fillWidth: true
                visible: viewModel.memberModel.count === 0
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 0

                Repeater {
                    id: membersList
                    model: viewModel.memberModel
                    delegate: MemberSelectableDelegate {}
                }
            }

            Item {
                height: btnNew.implicitHeight
            }
        }
    }

    XPane {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 16
        radius: height / 2
        Material.elevation: 3
        padding: 2
        visible: opacity > 0
        opacity: viewModel.isWorking ? 1 : 0
        Behavior on opacity { NumberAnimation { duration: 100 } }

        BusyIndicator {
            anchors.centerIn: parent
            implicitWidth: 32
            implicitHeight: 32
        }
    }

    XToast {
        id: toast
    }

    XRoundButton {
        id: btnNew
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        icon.source: "qrc:/img/icons/check.svg"
        onClicked: {
            if(txfName.text.length > 0 && txfDescription.text.length > 0 && selectedIndexes.length > 0) {
                viewModel.createProject(txfName.text, txfDescription.text, selectedIndexes)
            } else {
                toast.showText(qsTr("There are empty fields"))
            }
        }
    }
}
