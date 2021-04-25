QT +=   quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
    include/canbus.h \
    include/inversekinematics.h

SOURCES += \
        src/canbus.cpp \
        src/inversekinematics.cpp \
        src/main.cpp

RESOURCES += qml/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

INCLUDEPATH +=  /usr/include/eigen3

target.path = /home/pi/StewartPlatform/bin
INSTALLS += target
