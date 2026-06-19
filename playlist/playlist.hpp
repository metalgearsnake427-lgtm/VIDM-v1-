#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>

class PlaylistInterface : public QMainWindow {
    Q_OBJECT

public:
    explicit PlaylistInterface(QWidget *parent = nullptr);

private slots:
    void onTrackSelected(QListWidgetItem *item);
    void onPlayClicked();

private:
    QListWidget *sidebar;
    QListWidget *trackList;
    QLabel *nowPlayingLabel;
    QPushButton *playBtn;
    
    void setupInterface(); 
};

#endif
