#ifndef MEDIA_H
#define MEDIA_H
#include "QtMultimedia/QMediaPlayer"
#include "QtMultimedia/QMediaPlaylist"
#include "QtMultimedia/QMediaContent"
#include "qurl.h"
#include <QtMultimediaWidgets>


class media
{
public:
    media();

public slots:
    void startPlay();

};

#endif // MEDIA_H
