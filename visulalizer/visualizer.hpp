#ifndef VISUALIZER_HPP
#define VISUALIZER_HPP

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <vector>
#include <cmath>

class VisualizerWidget : public QWidget {
    Q_OBJECT
public:
    explicit VisualizerWidget(QWidget *parent = nullptr);
    void addAmplitude(float amplitude);
protected:
    void paintEvent(QPaintEvent *event) override;
private slots:
    void updateAnimation();
private:
    std::vector<float> amplitudes;
    QTimer *timer;
    void generateSampleData();
};

#endif
