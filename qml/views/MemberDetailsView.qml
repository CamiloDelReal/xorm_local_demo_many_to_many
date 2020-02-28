import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

import XApps.XOrmDemoManyToMany 1.0

import "qrc:/qml"

XPane {
    id: memberDetailsView

    property var memberGuid: sharedData

    Component.onCompleted: {
        viewModel.readMember(memberGuid)
    }

    MemberDetailsViewModel {
        id: viewModel
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
                text: qsTr("Member")
            }

            XCaptionLabel {
                text: qsTr("Full Name")
                color: memberDetailsView.Material.secondaryTextColor
                Layout.fillWidth: true
                Layout.topMargin: 12
            }

            XSubheadingLabel {
                Layout.fillWidth: true
                text: viewModel.currentMember !== null
                      ? viewModel.currentMember.name
                      : "--"
            }

            XCaptionLabel {
                text: qsTr("Job")
                color: memberDetailsView.Material.secondaryTextColor
                Layout.fillWidth: true
                Layout.topMargin: 12
            }

            XSubheadingLabel {
                Layout.fillWidth: true
                text: viewModel.currentMember !== null
                      ? viewModel.currentMember.job
                      : "--"
            }

            XCaptionLabel {
                Layout.fillWidth: true
                Layout.topMargin: 12
                text: qsTr("Projects")
                color: memberDetailsView.Material.secondaryTextColor
            }

            XBodyLabel1 {
                text: qsTr("No project defined for this member")
                horizontalAlignment: Label.AlignHCenter
                color: Material.color(Material.Red)
                Layout.fillWidth: true
                visible: viewModel.projectModel.count === 0
            }

            Repeater {
                model: viewModel.projectModel
                delegate: ColumnLayout {
                    Layout.fillWidth: true
                    Layout.leftMargin: 12
                    Layout.rightMargin: 12

                    XSubheadingLabel {
                        Layout.fillWidth: true
                        text: name
                    }
                    XCaptionLabel {
                        Layout.fillWidth: true
                        text: description
                    }
                }
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

}
