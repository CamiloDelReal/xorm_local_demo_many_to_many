import QtQuick
import QtQuick.Controls
import QtQuick.Controls.impl
import QtQuick.Controls.Material
import QtQuick.Layouts

import XApps.XOrmDemoManyToMany

import "qrc:/qml"
import "qrc:/qml/delegates"
import "qrc:/qml/listeners"


XPane {
    id: projectListingView
    title: qsTr("Projects List")

    Component.onCompleted: {
        viewModel.readProjects()
    }

    ProjectListingViewModel {
        id: viewModel
    }

    ProjectListingListener {
        id: listener

        function update() {
            // Maybe is better to call a different function to read only the new ones
            viewModel.readProjects()
        }
    }

    ListView {
        id: projectListView
        anchors.fill: parent
        ScrollIndicator.vertical: ScrollIndicator {}
        model: viewModel.projectModel
        delegate: ProjectDelegate {}
    }

    Rectangle {
        anchors.fill: parent
        color: projectListView.Material.background
        visible: opacity > 0
        opacity: viewModel.projectModel.count === 0 ? 1 : 0
        Behavior on opacity { NumberAnimation { duration: 150 } }

        ColumnLayout {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.right: parent.right

            IconLabel {
                Layout.alignment: Qt.AlignHCenter
                icon.source: "qrc:/img/icons/layers-off-outline.svg"
                icon.color: projectListView.Material.secondaryTextColor
                icon.width: 50
                icon.height: 50
            }

            XCaptionLabel {
                Layout.alignment: Qt.AlignHCenter
                Layout.leftMargin: 50
                Layout.rightMargin: 50
                Layout.fillWidth: true
                text: qsTr("No projects inserted, please touch the plus button to insert a new one")
                horizontalAlignment: Label.AlignHCenter
                wrapMode: Label.WordWrap
                color: projectListView.Material.secondaryTextColor
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

    XRoundButton {
        id: btnNew
        anchors.right: parent.right
        anchors.rightMargin: 8
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        icon.source: "qrc:/img/icons/plus.svg"
        onClicked: projectNavController.gotoView(projectNavController.projectEditionViewIndex, listener)
    }
}
