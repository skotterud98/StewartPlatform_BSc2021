QT +=   charts qml quick gui core

CONFIG +=   c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
        canbus.h \
        controller.h \
        imode.h \
        inversekinematics.h \
        oscillator.h \
        worker.h

SOURCES += \
        canbus.cpp \
        controller.cpp \
        imode.cpp \
        inversekinematics.cpp \
        main.cpp \
        oscillator.cpp \
        worker.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

INCLUDEPATH +=  /usr/include/eigen3

target.path = /home/pi/StewartPlatform/bin
INSTALLS += target

#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target
