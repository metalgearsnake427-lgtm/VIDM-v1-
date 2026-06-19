#include "interface.hpp"
#include <QDebug>
#include <QMessageBox>

enum class PlayerState {
    Ready,
    Playing,
    Paused,
    Replaying
};

class PlayerInterface : public QMainWindow {
    Q_OBJECT

public:
    PlayerInterface(QWidget *parent = nullptr);
    ~PlayerInterface();

private slots:
    void on_play_clicked();
    void on_pause_clicked();
    void on_replay_clicked();

private:
    void setupUI();
    void updateStatus(PlayerState state);
    
    QLabel *statusLabel;
    QPushButton *playButton;
    QPushButton *pauseButton;
    QPushButton *replayButton;
    PlayerState currentState;
};

PlayerInterface::PlayerInterface(QWidget *parent) : QMainWindow(parent), currentState(PlayerState::Ready) {
    setupUI();
}

PlayerInterface::~PlayerInterface() {}

void PlayerInterface::setupUI() {
    auto *centralWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(centralWidget);

    statusLabel = new QLabel("Status: Ready", this);
    playButton = new QPushButton("Play", this);
    pauseButton = new QPushButton("Pause", this);
    replayButton = new QPushButton("Replay", this);

    layout->addWidget(statusLabel);
    layout->addWidget(playButton);
    layout->addWidget(pauseButton);
    layout->addWidget(replayButton);

    setCentralWidget(centralWidget);

    connect(playButton, &QPushButton::clicked, this, &PlayerInterface::on_play_clicked);
    connect(pauseButton, &QPushButton::clicked, this, &PlayerInterface::on_pause_clicked);
    connect(replayButton, &QPushButton::clicked, this, &PlayerInterface::on_replay_clicked);
}

void PlayerInterface::on_play_clicked() {
    if (currentState == PlayerState::Playing) {
        QMessageBox::warning(this, "Warning", "Already playing!");
        return;
    }
    updateStatus(PlayerState::Playing);
    qDebug() << "GUI: Play requested";
}

void PlayerInterface::on_pause_clicked() {
    if (currentState == PlayerState::Paused) {
        QMessageBox::warning(this, "Warning", "Already paused!");
        return;
    }
    updateStatus(PlayerState::Paused);
    qDebug() << "GUI: Pause requested";
}

void PlayerInterface::on_replay_clicked() {
    if (currentState == PlayerState::Replaying) {
        QMessageBox::warning(this, "Warning", "Already replaying!");
        return;
    }
    updateStatus(PlayerState::Replaying);
    qDebug() << "GUI: Replay requested";
}

void PlayerInterface::updateStatus(PlayerState state) {
    currentState = state;
    switch (state) {
        case PlayerState::Playing:
            statusLabel->setText("Status: Playing");
            break;
        case PlayerState::Paused:
            statusLabel->setText("Status: Paused");
            break;
        case PlayerState::Replaying:
            statusLabel->setText("Status: Replaying");
            break;
        default:
            statusLabel->setText("Status: Ready");
            break;
    }
}
