import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.impl 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

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
