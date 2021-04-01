import QtQuick
import QtQuick.Controls

import "qrc:/qml"

XPane {
    id: projectsView
    padding: 0

    property alias navController: projectNavController

    function back() {
        if(projectNavController.depth > 1) {
            projectNavController.goBack()
            return true
        }
        return false
    }

    XViewNavController {
        id: projectNavController
        anchors.fill: parent

        initialView: ProjectListingView {}

        property int projectEditionViewIndex: 0
        property int projectDetailsViewIndex: 1
        viewNavigationModel: [
            { view: "views/ProjectEditionView.qml", stacked: true },
            { view: "views/ProjectDetailsView.qml", stacked: true }
        ]
    }
}
