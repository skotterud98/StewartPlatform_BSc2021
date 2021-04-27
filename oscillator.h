#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <QObject>
#include <QDebug>
#include <QVector>
#include <QString>

#include <math.h>
#include <vector>

#define PI 3.14159265358979323846


class Oscillator : public QObject
{
    Q_OBJECT
public:
    explicit Oscillator(QObject *parent = nullptr);

    std::vector<std::vector<double>> sample_sine(const double& t);

    double get_slider_surge();
    double get_slider_sway();
    double get_slider_heave();
    double get_slider_roll();
    double get_slider_pitch();
    double get_slider_yaw();

signals:
    void surge_changed(const int& param_value);
    void sway_changed(const int& param_value);
    void heave_changed(const int& param_value);
    void roll_changed(const int& param_value);
    void pitch_changed(const int& param_value);
    void yaw_changed(const int& param_value);

public slots:
    void set_surge(const double& slider_value);
    void set_sway(const double& slider_value);
    void set_heave(const double& slider_value);
    void set_roll(const double& slider_value);
    void set_pitch(const double& slider_value);
    void set_yaw(const double& slider_value);
    void set_amp();
    void set_freq();
    void set_phase();

private:
    double surge_A = 0.;
    double surge_bias = 0.;
    double surge_offset = 0.;
    double surge_freq = 0.;

    double sway_A = 0.;
    double sway_bias = 0.;
    double sway_offset = -PI/2;
    double sway_freq = 0.;

    double heave_A = 0.;
    double heave_bias = 0.04853;
    double heave_offset = 0.;
    double heave_freq = 0.;

    double roll_A = 0.;
    double roll_bias = 0.;
    double roll_offset = 0.;
    double roll_freq = 0.;

    double pitch_A = 0.;
    double pitch_bias = 0.;
    double pitch_offset = -PI/2;
    double pitch_freq = 0.;

    double yaw_A = 0.;
    double yaw_bias = 0.;
    double yaw_offset = 0.;
    double yaw_freq = 0.;

    double gain_A[6] = { 0.04, 0.04, 0.04, 10., 10., 35. };
    double gain_phase[6] = { PI, PI, PI, PI, PI, PI };
    double gain_freq[6] = { 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };

    enum pos_vel
    {
        POS = 0,
        VEL = 1
    };

    enum STATE
    {
        AMPLITUDE = 0,
        PHASE = 1,
        FREQUENCY = 2
    } gui_state;
};

#endif // OSCILLATOR_H
