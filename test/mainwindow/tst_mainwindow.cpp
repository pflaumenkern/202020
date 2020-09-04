#include <QtTest>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QPushButton>
#include <QStatusBar>
#include <QDebug>

#include "../../main/mainwindow.hpp"
#include "dialogfactorystub.hpp"
#include "settings.hpp"

class TestMainWindow : public QObject
{
    Q_OBJECT

public:
    TestMainWindow();
    ~TestMainWindow();

    static QtMsgType LAST_MSG_TYPE;
    static QString LAST_MSG;

private slots:
    void test_constructor();
    void test_timerButton();
    void test_setToggleStyle_running();
    void test_setToggleStyle_paused();
    void test_setStatusMessage();
    void test_aboutAction();
    void test_aboutAction_noFactory();
    void test_exitAction();

private:
    static void spyMessageHandler(QtMsgType, const QMessageLogContext &, const QString &);
};

QtMsgType TestMainWindow::LAST_MSG_TYPE = QtMsgType::QtDebugMsg;
QString TestMainWindow::LAST_MSG = "";

TestMainWindow::TestMainWindow()
{

}

TestMainWindow::~TestMainWindow()
{
    qInstallMessageHandler(nullptr);
}

void TestMainWindow::test_constructor()
{
    DialogFactoryStub factoryStub;
    MainWindow mainWindow(&factoryStub);
    mainWindow.show();

    auto timerButton = mainWindow.findChild<QPushButton *>("timerButton");
    auto message = mainWindow.findChild<QStatusBar *>("statusbar")->currentMessage();
    auto hasSettingsWidget = mainWindow.settingsWidget() != nullptr;

    bool isActive = QTest::qWaitForWindowActive(&mainWindow);

    Q_UNUSED(isActive);
    QCOMPARE(timerButton->text(), "Start");
    QVERIFY(timerButton->hasFocus());
    QVERIFY(message.isEmpty());
    QVERIFY(hasSettingsWidget);
}

void TestMainWindow::test_timerButton()
{
    MainWindow mainWindow;

    auto timerButton = mainWindow.findChild<QPushButton *>("timerButton");
    QSignalSpy clickSignal(&mainWindow, &MainWindow::toggleClicked);

    QTest::mouseClick(timerButton, Qt::LeftButton);

    QCOMPARE(clickSignal.count(), 1);
}

void TestMainWindow::test_setToggleStyle_running()
{
    MainWindow mainWindow;
    mainWindow.setToggleStyle(MainWindow::RUNNING);

    auto timerButton = mainWindow.findChild<QPushButton *>("timerButton");

    QCOMPARE(timerButton->text(), "Pause");
}

void TestMainWindow::test_setToggleStyle_paused()
{
    MainWindow mainWindow;
    mainWindow.setToggleStyle(MainWindow::PAUSED);

    auto timerButton = mainWindow.findChild<QPushButton *>("timerButton");

    QCOMPARE(timerButton->text(), "Start");
}

void TestMainWindow::test_setStatusMessage()
{
    QString expectedMessage = "TEST MESSAGE";
    MainWindow mainWindow;

    mainWindow.setStatusMessage(expectedMessage);

    auto actualMessage = mainWindow.findChild<QStatusBar *>("statusbar")->currentMessage();

    QCOMPARE(actualMessage, expectedMessage);
}

void TestMainWindow::test_aboutAction()
{
    qInstallMessageHandler(spyMessageHandler);

    DialogFactoryStub dialogFactoryStub;
    MainWindow mainWindow(&dialogFactoryStub);

    auto aboutAction = mainWindow.findChild<QMenu *>("menu_Help")->actions()[0];
    aboutAction->trigger();

    QCOMPARE(LAST_MSG_TYPE, QtMsgType::QtDebugMsg);
    QCOMPARE(LAST_MSG, "");
    QVERIFY(dialogFactoryStub.createHasBeenCalled());
    QVERIFY(dialogFactoryStub.openOnCreatedDialogCalled());
}

void TestMainWindow::test_aboutAction_noFactory()
{
    qInstallMessageHandler(spyMessageHandler);

    MainWindow mainWindow;

    auto aboutAction = mainWindow.findChild<QMenu *>("menu_Help")->actions()[0];
    aboutAction->trigger();

    QCOMPARE(LAST_MSG_TYPE, QtMsgType::QtWarningMsg);
    QCOMPARE(LAST_MSG, "No factory for about dialog provided.");
}

void TestMainWindow::test_exitAction()
{
    MainWindow mainWindow;
    mainWindow.show();

    bool isActive = QTest::qWaitForWindowActive(&mainWindow);
    auto fileMenu = mainWindow.findChild<QMenu *>("menu_File");

    fileMenu->actions()[0]->trigger();

    Q_UNUSED(isActive);
    QCOMPARE(mainWindow.isVisible(), false);
}

void TestMainWindow::spyMessageHandler(QtMsgType msgType, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);

    LAST_MSG_TYPE = msgType;
    LAST_MSG = msg;
}

QTEST_MAIN(TestMainWindow)

#include "tst_mainwindow.moc"
