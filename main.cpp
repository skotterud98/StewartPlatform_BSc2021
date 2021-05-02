#include <QtWidgets/QApplication>
#include <QtQuick/QQuickView>
#include <QtCore/QDir>
#include <QtQml/QQmlEngine>
#include <QQmlContext>

#include "oscillator.h"
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQuickView viewer;
    QQmlContext* context = viewer.engine()->rootContext();

    Oscillator* oscillator = new Oscillator;
    Controller* controller = new Controller(oscillator);

    context->setContextProperty("_oscillator", oscillator);
    context->setContextProperty("_controller", controller);


    QObject::connect(viewer.engine(), &QQmlEngine::quit, &viewer, &QWindow::close);

    viewer.setTitle(QStringLiteral("QML Chart"));

    viewer.setSource(QUrl("qrc:/qml/main.qml"));
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.show();

    return app.exec();
}







