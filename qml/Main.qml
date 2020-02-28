import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14

import "qrc:/qml"
import "qrc:/qml/pages"

XApplication {
    id: appRoot
    visible: true
    width: 420
    height: 600
    title: qsTr("XOrm Demo One")

    Material.theme: ApplicationSettingsObj.theme
    Material.primary: ApplicationSettingsObj.primaryColor
    Material.accent: ApplicationSettingsObj.accentColor

    onAppNavControllerCreated: {
        if(Qt.platform.os == "android" || Qt.platform.os == "ios") {
            ApplicationManagerObj.setUiReady(true)
        }
    }

    function initialization() {
        ApplicationManagerObj.initialize()
        appNavController.gotoView(appRoot.onHomePageIndex)
    }

    splashViewSourceComponent: SplashPage {}

    property int onHomePageIndex:   0
    viewNavigationModel: [
        { view: "pages/HomePage.qml",   stacked: false }
    ]
}
