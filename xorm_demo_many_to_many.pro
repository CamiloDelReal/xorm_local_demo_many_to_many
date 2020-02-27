#************  Qt Configurations  *****************************************************************
QT += qml quick quickcontrols2 svg xml
CONFIG += c++11 #qtquickcompiler
DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000


#************  X 3rd Party Libs  ******************************************************************


#************  X Modules  *************************************************************************
include($$PWD/../../libraries/x_material_controls/x_material_controls.pri)
include($$PWD/../../libraries/x_orm/x_orm.pri)
include($$PWD/../../libraries/x_utils/x_utils.pri)


#************  QML Configurations  ****************************************************************
QML_IMPORT_PATH += $$PWD/qml
QML_DESIGNER_IMPORT_PATH =


#************  App Sources  ***********************************************************************
HEADERS += \
    $$PWD/src/app/applicationmanager.hpp \
    $$PWD/src/app/applicationsettings.hpp \
    $$PWD/src/models/membermodel.hpp \
    $$PWD/src/models/projectmodel.hpp \
    $$PWD/src/services/entities/member.hpp \
    $$PWD/src/services/entities/memberproject.hpp \
    $$PWD/src/services/entities/project.hpp \
    $$PWD/src/services/local/databasemanager.hpp \
    $$PWD/src/viewmodels/memberlistingviewmodel.hpp \
    $$PWD/src/viewmodels/memberdetailsviewmodel.hpp \
    $$PWD/src/viewmodels/membereditionviewmodel.hpp \
    $$PWD/src/viewmodels/projectdetailsviewmodel.hpp \
    $$PWD/src/viewmodels/projecteditionviewmodel.hpp \
    $$PWD/src/viewmodels/projectlistingviewmodel.hpp

SOURCES += \
    $$PWD/src/app/main.cpp \
    $$PWD/src/app/applicationmanager.cpp \
    $$PWD/src/app/applicationsettings.cpp \
    $$PWD/src/models/membermodel.cpp \
    $$PWD/src/models/projectmodel.cpp \
    $$PWD/src/services/entities/member.cpp \
    $$PWD/src/services/entities/memberproject.cpp \
    $$PWD/src/services/entities/project.cpp \
    $$PWD/src/services/local/databasemanager.cpp \
    $$PWD/src/viewmodels/memberlistingviewmodel.cpp \
    $$PWD/src/viewmodels/memberdetailsviewmodel.cpp \
    $$PWD/src/viewmodels/membereditionviewmodel.cpp \
    $$PWD/src/viewmodels/projectdetailsviewmodel.cpp \
    $$PWD/src/viewmodels/projecteditionviewmodel.cpp \
    $$PWD/src/viewmodels/projectlistingviewmodel.cpp

INCLUDEPATH += \
    $$PWD/src/app \
    $$PWD/src/models \
    $$PWD/src/services/entities \
    $$PWD/src/services/local \
    $$PWD/src/services/remote \
    $$PWD/src/viewmodels


#************  Resources  *************************************************************************
RESOURCES += \
    $$PWD/resources.qrc


#************  Images Files  **********************************************************************
DISTFILES +=  \
    $$PWD/img/app/icon_launcher.svg \
    $$PWD/img/app/logo.svg \
    $$PWD/img/app/logo_foreground.svg \
    $$PWD/img/icons/account-off-outline.svg \
    $$PWD/img/icons/arrow-left.svg \
    $$PWD/img/icons/check.svg \
    $$PWD/img/icons/delete.svg \
    $$PWD/img/icons/layers-off-outline.svg \
    $$PWD/img/icons/magnify.svg \
    $$PWD/img/icons/plus.svg


#************  QML Files  *************************************************************************
DISTFILES += \
    $$PWD/qml/Main.qml \
    $$PWD/qml/delegates/MemberDelegate.qml \
    $$PWD/qml/delegates/MemberSelectableDelegate.qml \
    $$PWD/qml/delegates/ProjectDelegate.qml \
    $$PWD/qml/delegates/ProjectSelectableDelegate.qml \
    $$PWD/qml/listeners/MemberListingListener.qml \
    $$PWD/qml/listeners/ProjectListingListener.qml \
    $$PWD/qml/pages/SplashPage.qml \
    $$PWD/qml/pages/HomePage.qml \
    $$PWD/qml/views/MemberDetailsView.qml \
    $$PWD/qml/views/MemberEditionView.qml \
    $$PWD/qml/views/MemberListingView.qml \
    $$PWD/qml/views/MembersView.qml \
    $$PWD/qml/views/ProjectDetailsView.qml \
    $$PWD/qml/views/ProjectEditionView.qml \
    $$PWD/qml/views/ProjectListingView.qml \
    $$PWD/qml/views/ProjectsView.qml


##************  Android Configurations  ************************************************************
android {
    QT += androidextras
    DISTFILES += \
        $$PWD/android/AndroidManifest.xml \
        $$PWD/android/gradle/wrapper/gradle-wrapper.jar \
        $$PWD/android/gradle/wrapper/gradle-wrapper.properties \
        $$PWD/android/gradlew \
        $$PWD/android/gradlew.bat \
        $$PWD/android/build.gradle \
        $$PWD/android/res/values/libs.xml \
        $$PWD/android/res/drawable/splash.xml \
        $$PWD/android/res/mipmap-ldpi/icon_launcher.png \
        $$PWD/android/res/mipmap-mdpi/icon_launcher.png \
        $$PWD/android/res/mipmap-hdpi/icon_launcher.png \
        $$PWD/android/res/mipmap-xhdpi/icon_launcher.png \
        $$PWD/android/res/mipmap-xxhdpi/icon_launcher.png \
        $$PWD/android/res/mipmap-xxxhdpi/icon_launcher.png

    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}

#contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
#    QT += androidextras
#    ANDROID_PACKAGE_SOURCE_DIR = \
#        $$PWD/android
#}
