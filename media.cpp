#include "media.h"


media::media()
{

}
void media::startPlay(){


   QMediaPlayer * player = new QMediaPlayer();

   QMediaPlaylist * playlist = new QMediaPlaylist(player);
    playlist->addMedia(QUrl::fromLocalFile("Live It Up - Nicky Jam feat. Will Smith & Era Istrefi .mp3"));
    playlist->addMedia(QUrl("http://air.radioulitka.ru:8000/ulitka_96"));
    playlist->setCurrentIndex(0);
    player->setVolume(30);
    player->play();
}
