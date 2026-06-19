#ifndef PLAYERINTERFACE_HPP
#define PLAYERINTERFACE_HPP

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

class PlayerInterface : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayerInterface(QWidget *parent = nullptr);
    ~PlayerInterface() override;

private slots:
    void on_play_clicked();
    void on_pause_clicked();
    void on_replay_clicked();

private:
    QLabel *statusLabel = nullptr;
    QPushButton *playButton = nullptr;
    QPushButton *pauseButton = nullptr;
    QPushButton *replayButton = nullptr;
};

#endif // PLAYERINTERFACE_HPP
