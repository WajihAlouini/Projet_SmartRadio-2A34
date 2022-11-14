#include "invite.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QString>
#include "mainwindow.h"
#include "mainwindow.cpp"
#include "ui_mainwindow.h"
#include <QSqlQueryModel>
#include <QTime>
#include <QTimeEdit>
#include <QAudioInput>
#include "Micro.h"
#include <QAudioRecorder>
#include <QAudioEncoderSettings>
 audioRecorder = new QAudioRecorder;

QAudioEncoderSettings audioSettings;
audioSettings.setCodec("audio/amr");
audioSettings.setQuality(QMultimedia::HighQuality);

audioRecorder->setEncodingSettings(audioSettings);

audioRecorder->setOutputLocation(QUrl::fromLocalFile("test.amr"));
audioRecorder->record();
