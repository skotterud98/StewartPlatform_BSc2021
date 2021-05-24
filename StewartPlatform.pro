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
        joystick.h \
        modeworker.h \
        neutral.h \
        oscillator.h \
        park.h \
        rampneutral.h

SOURCES += \
        canbus.cpp \
        controller.cpp \
        inversekinematics.cpp \
        joystick.cpp \
        main.cpp \
        modeworker.cpp \
        neutral.cpp \
        oscillator.cpp \
        park.cpp \
        rampneutral.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

INCLUDEPATH +=  /usr/include/eigen3

# Target path on the raspberry pi
target.path = /home/pi/StewartPlatform/bin
INSTALLS += target
