#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDate>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QMap>
#include <QMessageBox>
#include <QPixmap>
#include <QRect>
#include <QScreen>
#include <QStandardPaths>
#include <QSqlRecord>
#include <QTime>
#include <QTimer>

#include "database.hpp"
#include "chart.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace CallsCounter { class MainWindow; };

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Ui::MainWindow *m_ui;
    QMap<int, QString> m_calls;
    QMap<int, QString> m_notSavedCalls;
    bool m_modified;
    int m_totalCalls;
    QString m_datetime;
    QString m_username;
    Chart* m_chart;
    QTimer m_lockerTimer;
    QTimer m_saverTimer;
    QTimer m_saverTimer1s;
    QTimer m_datetimeTimer;
    bool m_lock;
    Database m_db;

    void setLabel(bool justMessageLabel, const QString& prefix);
    void setDateTime();
    void setTodaysCalls();
    bool isDBEmpty();
    int dayOfWeek();
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
private slots:
    void about(bool checked);
    void unlockNewButton();
    void error(const QString& message);
    void newCall();
    void removeCall();
    void saveCalls();
    void setRemainingTimeLabel();
    void updateHoveredLabel(const QString& label);
};

#endif // MAINWINDOW_H
