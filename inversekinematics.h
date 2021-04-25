#ifndef INVERSEKINEMATICS_H
#define INVERSEKINEMATICS_H

#include <QObject>

class InverseKinematics : public QObject
{
    Q_OBJECT
public:
    explicit InverseKinematics(QObject *parent = nullptr);

signals:

};

#endif // INVERSEKINEMATICS_H
