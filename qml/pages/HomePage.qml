import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

import "qrc:/qml"
import "qrc:/qml/views"

XTitledTabbedPage {
    id: homePage
    statusBarHeight: ApplicationManagerObj.systemStatusBarSize

    Component.onCompleted: {
        homeNavController.gotoView(homeNavController.membersViewIndex)
    }

    titlebar.title: qsTr("XOrm Demo Many to Many")
    titlebar.primaryAction: homeNavController.currentItem && homeNavController.currentItem.navController.depth > 1
                            ? primaryAction
                            : null

    XAction {
        id: primaryAction
        text: qsTr("Open global drawer")
        icon.source: "qrc:/img/icons/arrow-left.svg"
        onTriggered: homePage.back()
    }

    tabbar.tabActions: [
        XAction {
            text: qsTr("Members")
            checked: true
            onTriggered: homeNavController.gotoView(homeNavController.membersViewIndex)
        },
        XAction {
            text: qsTr("Projects")
            onTriggered: homeNavController.gotoView(homeNavController.projectsViewIndex)
        }
    ]

    function back() {
        return homeNavController.currentItem.back()
//        if(homeNavController.currentItem.back()) {
//            return true
//        }
//        return false
    }

    XViewNavController {
        id: homeNavController
        anchors.fill: parent

        property int membersViewIndex:  0
        property int projectsViewIndex:  1
        viewNavigationModel: [
            { view: "views/MembersView.qml",    stacked: false },
            { view: "views/ProjectsView.qml",   stacked: false }
        ]
    }

}
