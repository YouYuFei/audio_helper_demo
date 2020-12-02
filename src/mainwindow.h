#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define CHINAWEATHERDATA "org.china-weather-data.settings"
#define FITTHEMEWINDOW "org.ukui.style"

//*********************************支持语音助手****************************************
#define AUDIO_API_MODULE_NAME_LEN 32
#define SETTINGS_AUDIO_API_SCHEMAS "org.ukui.audio_api"
#define APP_NAME "indicator-china-weather"
#define SHOW_WINDOW 1
#include <QDBusInterface>
#include <QDBusConnection>
//*********************************支持语音助手****************************************

#include "mainwindow.h"
#include "leftupcitybtn.h"
#include "leftupsearchbox.h"
#include "leftupsearchview.h"
#include "leftupsearchdelegate.h"
#include "informationwidget.h"
#include "locationworker.h"
#include "weathermanager.h"
#include "promptwidget.h"
#include "data.h"

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <xcb/xcb.h>

#include <QMainWindow>
#include <QStandardPaths>
#include <QMouseEvent>
#include <QDebug>
#include <QButtonGroup>
#include <QObjectUserData>
#include <QSortFilterProxyModel>
#include <QScrollArea>
#include <QScrollBar>
#include <QWidget>
#include <QSystemTrayIcon>
#include <QRect>
#include <QScreen>
#include <QDesktopWidget>
#include <QTime>
#include <QTimer>
#include <QFileInfo>
#include <QLocale>
#include <QPainterPath>
#include <QMenu>
#include <QAction>

#include <QGSettings>
#include <QGraphicsDropShadowEffect>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void createTrayIcon();
    void handleIconClicked();
    void handleIconClickedSub();

    void onRefreshMainWindowWeather();
    void onHandelAbnormalSituation(QString abnormalText);

    void onSetForecastWeather(ForecastWeather m_forecastweather);
    void onSetObserveWeather(ObserveWeather m_observeweather);
    void onSetLifeStyle(LifeStyle m_lifestyle);

//*********************************支持语音助手****************************************
    void ukui_module_init();
    void ukui_module_dbus_reg(void);
    int ukui_module_exe_cmd_api(int cmd);
    void ukui_module_register(QString key);
//*********************************支持语音助手****************************************

private slots:
    void on_btnMinimize_clicked();

    void on_btnCancel_clicked();

    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void closeActivated();

private:
    QGSettings *mAudioApiInitSetting;//支持语音助手
    Ui::MainWindow *ui;
    QScrollArea *m_scrollarea = nullptr;
    QWidget *m_scrollwidget = nullptr;
    LeftUpCityBtn *m_leftupcitybtn = nullptr;
    LeftUpSearchBox *m_leftupsearchbox = nullptr;
    WeatherManager* m_weatherManager = nullptr;
    PromptWidget *m_hintWidget = nullptr;
    PromptWidget *m_movieWidget = nullptr;
    LeftUpSearchView *m_searchView = nullptr;
    LeftUpSearchDelegate *m_delegate = nullptr;
    QSortFilterProxyModel* m_proxyModel = nullptr;
    QStandardItemModel *m_model = nullptr;
    LocationWorker *m_locationWorker = nullptr;
    Information *m_information;
    QSystemTrayIcon *m_trayIcon = nullptr;
    QTimer *m_refreshweather;
    QMenu *m_mainMenu = nullptr;
    QAction *m_openAction;
    QAction *m_quitAction;
    void judgeSystemLanguage();

    void onSearchBoxEdited();
    void searchCityName();

    void initControlQss();
    void initConnections();

    void setAbnormalMainWindow();

    QString convertCodeToBackgroud(int code);
    void convertCodeToTrayIcon(QString code);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    bool event(QEvent *event);
    bool isPress;
    QPoint winPos;
    QPoint dragPos;

    // getstting初始化、值获取、 设置getsetting值
    void initGsetting();
    QString getCityList();
    void setCityList(QString str);
    void setThemeStyle();

    QGSettings  *m_pWeatherData= nullptr;
    QGSettings  *m_pThemeStyle= nullptr;
    QString firstGetCityList="";

    QString nowThemeStyle;
signals:
    void updatecity();
};

#endif // MAINWINDOW_H
