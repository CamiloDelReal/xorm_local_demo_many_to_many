import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.impl 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

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
