#include "playlist.hpp"
#include <QListWidgetItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPropertyAnimation>

PlaylistInterface::PlaylistInterface(QWidget *parent) : QMainWindow(parent) {
    QWidget *central = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(central);

    // Sidebar - PSP/Spotify vibe
    sidebar = new QListWidget(this);
    sidebar->setFixedWidth(150);
    sidebar->addItems({"Home", "Library", "Playlists", "Settings"});
    
    // Main Track Area with Graphics View
    QVBoxLayout *contentLayout = new QVBoxLayout();
    nowPlayingLabel = new QLabel("Select a track...");
    nowPlayingLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #1DB954;");

    trackList = new QListWidget(this);
    trackList->addItems({"Video Track 01 - Intro.mp4", "Video Track 02 - Gameplay.mkv", "Video Track 03 - Ending.avi"});

    playBtn = new QPushButton("PLAY");
    playBtn->setFixedHeight(40);
    playBtn->setStyleSheet("background-color: #1DB954; border-radius: 20px; color: white;");

    contentLayout->addWidget(nowPlayingLabel);
    contentLayout->addWidget(trackList);
    contentLayout->addWidget(playBtn);

    mainLayout->addWidget(sidebar);
    mainLayout->addLayout(contentLayout);

    setCentralWidget(central);
    setupAesthetics();

    connect(trackList, &QListWidget::itemClicked, this, &PlaylistInterface::onTrackSelected);
    connect(playBtn, &QPushButton::clicked, this, &PlaylistInterface::onPlayClicked);
}

void PlaylistInterface::setupAesthetics() {
    this->setStyleSheet("background-color: #121212; color: white; selection-background-color: #333;");
    sidebar->setStyleSheet("background-color: #000; border: none; padding: 10px;");
    trackList->setStyleSheet("background-color: #121212; border: none; font-size: 14px;");
}

void PlaylistInterface::onTrackSelected(QListWidgetItem *item) {
    nowPlayingLabel->setText("Now Playing: " + item->text());
    // Add animation effect
    QPropertyAnimation *animation = new QPropertyAnimation(nowPlayingLabel, "opacity");
    animation->setDuration(500);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
}

void PlaylistInterface::onPlayClicked() {
    // Logic to bridge with C-Core engine
}
