import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.impl 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

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
