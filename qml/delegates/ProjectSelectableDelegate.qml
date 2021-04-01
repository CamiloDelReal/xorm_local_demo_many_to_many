import QtQuick
import QtQuick.Controls
import QtQuick.Controls.impl
import QtQuick.Controls.Material
import QtQuick.Layouts

import "qrc:/qml"

XCheckDelegate {
    id: projectDelegate
    Layout.fillWidth: true

    text: name
    secondaryText: description

    onCheckedChanged: {
        if(checked) {
            memberEditionView.selectedIndexes.push(index)
        } else {
            var position = memberEditionView.selectedIndexes.indexOf(index)
            memberEditionView.selectedIndexes.splice(position, 1)
        }
    }
}
