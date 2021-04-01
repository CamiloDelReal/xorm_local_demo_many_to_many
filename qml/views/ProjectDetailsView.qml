import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

import XApps.XOrmDemoManyToMany

import "qrc:/qml"

XPane {
    id: projectDetailsView

    property var projectGuid: sharedData

    Component.onCompleted: {
        viewModel.readProject(projectGuid)
    }

    ProjectDetailsViewModel {
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
                text: qsTr("Project")
            }

            XCaptionLabel {
                text: qsTr("Full Name")
                color: projectDetailsView.Material.secondaryTextColor
                Layout.fillWidth: true
                Layout.topMargin: 12
            }

            XSubheadingLabel {
                Layout.fillWidth: true
                text: viewModel.currentProject !== null
                      ? viewModel.currentProject.name
                      : "--"
            }

            XCaptionLabel {
                text: qsTr("Job")
                color: projectDetailsView.Material.secondaryTextColor
                Layout.fillWidth: true
                Layout.topMargin: 12
            }

            XSubheadingLabel {
                Layout.fillWidth: true
                text: viewModel.currentProject !== null
                      ? viewModel.currentProject.description
                      : "--"
            }

            XCaptionLabel {
                Layout.fillWidth: true
                Layout.topMargin: 12
                text: qsTr("Members")
                color: projectDetailsView.Material.secondaryTextColor
            }

            XBodyLabel1 {
                text: qsTr("No members defined for this project")
                horizontalAlignment: Label.AlignHCenter
                color: Material.color(Material.Red)
                Layout.fillWidth: true
                visible: viewModel.memberModel.count === 0
            }

            Repeater {
                model: viewModel.memberModel
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
                        text: job
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
