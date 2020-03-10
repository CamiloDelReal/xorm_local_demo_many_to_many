import QtQuick 2.14
import QtQuick.Controls 2.14

import "qrc:/qml"

XPane {
    id: membersView
    padding: 0

    property alias navController: memberNavController

    function back() {
        if(memberNavController.depth > 1) {
            memberNavController.goBack()
            return true
        }
        return false
    }

    XViewNavController {
        id: memberNavController
        anchors.fill: parent

        initialView: MemberListingView {}

        property int memberEditionViewIndex: 0
        property int memberDetailsViewIndex: 1
        viewNavigationModel: [
            { view: "views/MemberEditionView.qml", stacked: true },
            { view: "views/MemberDetailsView.qml", stacked: true }
        ]
    }
}
