#include <QtTest>
#include <QDialog>

#include "settings.hpp"
#include "settingswidget.hpp"
#include "../../main/mainwindow.hpp"
#include "../../main/mainwindowpresenter.hpp"

class TestMainWindowPresenter : public QObject
{
    Q_OBJECT
public:
    TestMainWindowPresenter();
    ~TestMainWindowPresenter();

private slots:
    void cleanupTestCase();
    void test_constructor_connections();
    void test_constructor_connections_withoutMainWindow();
    void test_constructor_connections_withoutReminder();
    void test_constructor_timerSettings();
    void test_constructor_autoRunSetting_false();
    void test_constructor_autoRunSetting_true();
    void test_toggleTimer_Start();
    void test_toggleTimer_Pause();
};

TestMainWindowPresenter::TestMainWindowPresenter()
{

}

TestMainWindowPresenter::~TestMainWindowPresenter()
{

}

void TestMainWindowPresenter::cleanupTestCase()
{
    Settings::setAutoRun(false);
}

void TestMainWindowPresenter::test_constructor_connections()
{
    MainWindow mainWindow;
    QDialog reminder;
    MainWindowPresenter presenter(&mainWindow, &reminder);
    auto timer = presenter.reminderTimer();

    auto mainWindowToggleConnected = !connect(&mainWindow, &MainWindow::toggleClicked, &presenter, &MainWindowPresenter::toggleTimer, Qt::UniqueConnection);
    auto presenterToggleStyleConnected = !connect(&presenter, &MainWindowPresenter::toggleStyleChanged, &mainWindow, &MainWindow::setToggleStyle, Qt::UniqueConnection);
    auto presenterStatusChangeConnected = !connect(&presenter, &MainWindowPresenter::statusChanged, &mainWindow, &MainWindow::setStatusMessage, Qt::UniqueConnection);
    auto reminderConnected = !connect(&reminder, &QDialog::finished, timer, QOverload<>::of(&QTimer::start), Qt::UniqueConnection);
    auto timerConnected = !connect(timer, &QTimer::timeout, &reminder, &QDialog::show, Qt::UniqueConnection);

    QVERIFY(mainWindowToggleConnected);
    QVERIFY(presenterToggleStyleConnected);
    QVERIFY(presenterStatusChangeConnected);
    QVERIFY(reminderConnected);
    QVERIFY(timerConnected);
}

void TestMainWindowPresenter::test_constructor_connections_withoutMainWindow()
{
    MainWindow mainWindow;
    MainWindowPresenter presenter(nullptr, nullptr);

    auto mainWindowToggleNotConnected = connect(&mainWindow, &MainWindow::toggleClicked, &presenter, &MainWindowPresenter::toggleTimer, Qt::UniqueConnection);
    auto presenterToggleStyleNotConnected = connect(&presenter, &MainWindowPresenter::toggleStyleChanged, &mainWindow, &MainWindow::setToggleStyle, Qt::UniqueConnection);
    auto presenterStatusChangeNotConnected = connect(&presenter, &MainWindowPresenter::statusChanged, &mainWindow, &MainWindow::setStatusMessage, Qt::UniqueConnection);

    QVERIFY(mainWindowToggleNotConnected);
    QVERIFY(presenterToggleStyleNotConnected);
    QVERIFY(presenterStatusChangeNotConnected);
}

void TestMainWindowPresenter::test_constructor_connections_withoutReminder()
{
    QDialog reminder;
    MainWindowPresenter presenter(nullptr, nullptr);
    auto timer = presenter.reminderTimer();

    auto reminderNotConnected = connect(&reminder, &QDialog::finished, timer, QOverload<>::of(&QTimer::start), Qt::UniqueConnection);
    auto timerNotConnected = connect(timer, &QTimer::timeout, &reminder, &QDialog::show, Qt::UniqueConnection);

    QVERIFY(reminderNotConnected);
    QVERIFY(timerNotConnected);
}

void TestMainWindowPresenter::test_constructor_timerSettings()
{
    MainWindow mainWindow;
    QDialog reminder;
    MainWindowPresenter presenter(&mainWindow, &reminder);

    bool statusTimerIsNotActive = !presenter.statusTimerIsActive();
    bool timerIsNotActive = !presenter.timerIsActive();
    bool timerIsSingleShot = presenter.timerIsSingleShot();
    bool timerIntervalEquals20Minutes = presenter.timerInterval() == 1200000;

    QVERIFY(statusTimerIsNotActive);
    QVERIFY(timerIsNotActive);
    QVERIFY(timerIsSingleShot);
    QVERIFY(timerIntervalEquals20Minutes);
}

void TestMainWindowPresenter::test_constructor_autoRunSetting_false()
{
    Settings::setAutoRun(false);

    MainWindow mainWindow;
    MainWindowPresenter presenter(&mainWindow, nullptr);

    bool timerIsActive = presenter.timerIsActive();

    QCOMPARE(timerIsActive, false);
}

void TestMainWindowPresenter::test_constructor_autoRunSetting_true()
{
    Settings::setAutoRun(true);

    MainWindow mainWindow;
    MainWindowPresenter presenter(&mainWindow, nullptr);

    bool timerIsActive = presenter.timerIsActive();

    QVERIFY(timerIsActive);
}

void TestMainWindowPresenter::test_toggleTimer_Start()
{
    Settings::setAutoRun(false);

    MainWindow mainWindow;
    QDialog dialog;
    MainWindowPresenter presenter(&mainWindow, &dialog);
    QSignalSpy statusChangedSpy(&presenter, &MainWindowPresenter::statusChanged);
    QSignalSpy toggleChangedSpy(&presenter, &MainWindowPresenter::toggleStyleChanged);

    presenter.toggleTimer();

    QCOMPARE(statusChangedSpy.count(), 1);
    QCOMPARE(statusChangedSpy.first()[0], "Next reminder in 20 minute(s).");
    QCOMPARE(toggleChangedSpy.count(), 1);
    QCOMPARE(toggleChangedSpy.first()[0], MainWindow::RUNNING);
}

void TestMainWindowPresenter::test_toggleTimer_Pause()
{
    Settings::setAutoRun(false);

    MainWindow mainWindow;
    QDialog dialog;
    MainWindowPresenter presenter(&mainWindow, &dialog);
    QSignalSpy statusChangedSpy(&presenter, &MainWindowPresenter::statusChanged);
    QSignalSpy toggleChangedSpy(&presenter, &MainWindowPresenter::toggleStyleChanged);

    presenter.toggleTimer();
    presenter.toggleTimer();

    QCOMPARE(statusChangedSpy.count(), 2);
    QCOMPARE(statusChangedSpy.last()[0], "Paused.");
    QCOMPARE(toggleChangedSpy.count(), 2);
    QCOMPARE(toggleChangedSpy.last()[0], MainWindow::PAUSED);
}

QTEST_MAIN(TestMainWindowPresenter)

#include "tst_mainwindowpresenter.moc"
