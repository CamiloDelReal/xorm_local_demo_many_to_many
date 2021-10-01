import QtQuick
import QtQuick.Controls
import QtQuick.Controls.impl
import QtQuick.Controls.Material
import QtQuick.Layouts

import XApps.XOrmDemoManyToMany

import "qrc:/qml"
import "qrc:/qml/delegates"

XPane {
    id: memberEditionView

    property var listingListener: sharedData

    property var selectedIndexes: []

    Component.onCompleted: {
        viewModel.readProjects()
    }

    MemberEditionViewModel {
        id: viewModel

        onMemberCreated: {
            listingListener.update()
            memberNavController.goBack()
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
                text: qsTr("New member")
            }

            XFormTextField {
                id: txfName
                placeholderText: qsTr("Full Name")
                font.pixelSize: 18
                Layout.fillWidth: true
                Layout.topMargin: 12
            }

            XFormTextField {
                id: txfJob
                placeholderText: qsTr("Job")
                wrapMode: TextArea.Wrap
                font.pixelSize: 14
                Layout.fillWidth: true
            }

            XTitleLabel {
                Layout.fillWidth: true
                Layout.topMargin: 16
                text: qsTr("Projects")
            }

            XBodyLabel1 {
                text: qsTr("No project defined, but is not mandatory to have projects defined")
                wrapMode: Label.WordWrap
                horizontalAlignment: Label.AlignHCenter
                color: Material.color(Material.DeepOrange)
                Layout.fillWidth: true
                visible: viewModel.projectModel.count === 0
            }

            ColumnLayout {
                Layout.fillWidth: true
                spacing: 0

                Repeater {
                    id: projectsList
                    model: viewModel.projectModel
                    delegate: ProjectSelectableDelegate {}
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
            if(txfName.text.length > 0 && txfJob.text.length > 0) {
                viewModel.createMember(txfName.text, txfJob.text, selectedIndexes)
            } else {
                toast.showText(qsTr("There are empty fields"))
            }
        }
    }
}
