import QtQuick
import QtQuick.Controls
import QtQuick.Controls.impl
import QtQuick.Controls.Material
import QtQuick.Layouts

import "qrc:/qml"

XCheckDelegate {
    id: memberDelegate
    Layout.fillWidth: true

    text: name
    secondaryText: job

    onCheckedChanged: {
        if(checked) {
            projectEditionView.selectedIndexes.push(index)
        } else {
            var position = projectEditionView.selectedIndexes.indexOf(index)
            projectEditionView.selectedIndexes.splice(position, 1)
        }
    }
}
