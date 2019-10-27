#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "storemodel.h"
#include "trayicon.h"
#include <QFileSystemModel>
#include <QMainWindow>
#include <QProcess>
#include <QQueue>
#include <QSettings>
#include <QTimer>
#include <QTreeView>
#if SINGLE_APP
#include "singleapplication.h"
#else
#define SingleApplication QApplication
#endif

namespace Ui {
class MainWindow;
}

/*!
    \struct execQueueItem
    \brief Execution queue items for non-interactive ordered execution.
 */
struct execQueueItem {
  /**
   * @brief app executable path.
   */
  QString app;
  /**
   * @brief args arguments for executable.
   */
  QString args;
  /**
   * @brief input stdio input.
   */
  QString input;
};

struct UserInfo;

/*!
    \struct passwordConfiguration
    \brief  holds the Password configuration settings
 */
struct passwordConfiguration {
  /**
   * @brief passwordConfiguration::selected character set.
   */
  int selected;
  /**
   * @brief passwordConfiguration::length of password.
   */
  int length;
  /**
   * @brief passwordConfiguration::Characters the different character sets.
   */
  QString Characters[4];
  passwordConfiguration() {
    length = 16;
    selected = 0;
    enum selected { ALLCHARS, ALPHABETICAL, ALPHANUMERIC, CUSTOM };
    Characters[ALLCHARS] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890~!@#$%^&"
        "*()_-+={}[]|:;<>,.?"; /*AllChars*/
    Characters[ALPHABETICAL] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstu"
                               "vwxyz"; /*Only Alphabetical*/
    Characters[ALPHANUMERIC] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstu"
                               "vwxyz1234567890"; /*Alphabetical and Numerical*/
    Characters[CUSTOM] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1"
                         "234567890~!@#$%^&*()_-+={}[]|:;<>,.?"; /*Custom*/
  }
};

/*!
    \class MainWindow
    \brief The MainWindow class does way too much, not only is it a switchboard,
    configuration handler and more, it's also the process-manager.

    This class could really do with an overhaul.
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

  enum actionType { GPG, GIT, EDIT, DELETE, GPG_INTERNAL, PWGEN };

public:
  /**
   * @brief MainWindow::clipBoardType enum
   * 0 Never
   * 1 Always
   * 2 On demand
   */
  enum clipBoardType {
    CLIPBOARD_NEVER = 0,
    CLIPBOARD_ALWAYS = 1,
    CLIPBOARD_ON_DEMAND = 2
  };

  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void setPassExecutable(QString);
  void setGitExecutable(QString);
  void setGpgExecutable(QString);
  QString getGpgExecutable();
  bool checkConfig();
  void setApp(SingleApplication *app);
  void setText(QString);
  QStringList getSecretKeys();
  void generateKeyPair(QString, QDialog *);
  void userDialog(QString = "");
  QString generatePassword(unsigned int length, clipBoardType selection);
  void config();
  void executePassGitInit();

  /**
   * @brief MainWindow::pwdConfig instance of passwordConfiguration.
   * @sa MainWindow::passwordConfiguration
   */
  passwordConfiguration pwdConfig;

protected:
  void closeEvent(QCloseEvent *event);
  void keyPressEvent(QKeyEvent *event);
  void changeEvent(QEvent *event);
  bool eventFilter(QObject *obj, QEvent *event);

private slots:
  void on_updateButton_clicked();
  void on_pushButton_clicked();
  void on_treeView_clicked(const QModelIndex &index);
  void on_treeView_doubleClicked(const QModelIndex &index);
  void on_configButton_clicked();
  void readyRead(bool finished);
  void processFinished(int, QProcess::ExitStatus);
  void processError(QProcess::ProcessError);
  void clearClipboard();
  void clearPanel();
  void on_lineEdit_textChanged(const QString &arg1);
  void on_lineEdit_returnPressed();
  void on_addButton_clicked();
  void on_deleteButton_clicked();
  void on_editButton_clicked();
  void on_usersButton_clicked();
  void messageAvailable(QString message);
  void on_profileBox_currentIndexChanged(QString);
  void on_copyPasswordButton_clicked();
  void showContextMenu(const QPoint &pos);
  void showBrowserContextMenu(const QPoint &pos);
  void addFolder();
  void editPassword();
  void focusInput();
  void copyPasswordToClipboard();

private:
  QAction *actionAddPassword;
  QAction *actionAddFolder;

  QApplication *QtPass;
  QScopedPointer<QSettings> settings;
  QScopedPointer<Ui::MainWindow> ui;
  QFileSystemModel model;
  StoreModel proxyModel;
  QScopedPointer<QItemSelectionModel> selectionModel;
  QScopedPointer<QProcess> process;
  bool usePass;
  clipBoardType useClipboard;
  bool useAutoclear;
  bool useAutoclearPanel;
  bool hidePassword;
  bool hideContent;
  bool addGPGId;
  int autoclearSeconds;
  int autoclearPanelSeconds;
  QString passStore;
  QString passExecutable;
  QString gitExecutable;
  QString gpgExecutable;
  QString pwgenExecutable;
  QString gpgHome;
  bool useWebDav;
  QString webDavUrl;
  QString webDavUser;
  QString webDavPassword;
  QProcess fusedav;
  QString clippedPass;
  QString autoclearPass;
  QTimer *autoclearTimer;
  actionType currentAction;
  QString lastDecrypt;
  bool wrapperRunning;
  QStringList env;
  QQueue<execQueueItem> *execQueue;
  bool freshStart;
  QDialog *keygen;
  QString currentDir;
  QHash<QString, QString> profiles;
  QString profile;
  bool startupPhase;
  TrayIcon *tray;
  bool useTrayIcon;
  bool hideOnClose;
  bool startMinimized;
  bool useGit;
  bool usePwgen;
  bool avoidCapitals;
  bool avoidNumbers;
  bool lessRandom;
  bool useSymbols;
  bool useTemplate;
  QString passTemplate;
  bool templateAllFields;
  bool autoPull;
  bool autoPush;
  bool alwaysOnTop;
  void updateText();
  void executePass(QString, QString = QString());
  void executeWrapper(QString, QString, QString = QString());
  void enableUiElements(bool state);
  void selectFirstFile();
  QModelIndex firstFile(QModelIndex parentIndex);
  QString getDir(const QModelIndex &, bool);
  QString getFile(const QModelIndex &, bool);
  void setPassword(QString, bool, bool);
  QSettings &getSettings();
  QList<UserInfo> listKeys(QString keystring = "", bool secret = false);
  QStringList getRecipientList(QString for_file);
  QString getRecipientString(QString for_file, QString separator = " ",
                             int *count = NULL);
  void mountWebDav();
  void updateEnv();
  void updateProfileBox();
  void initTrayIcon();
  void destroyTrayIcon();
  bool removeDir(const QString &dirName);
  void waitFor(int seconds);
  void clearTemplateWidgets();
  void setClippedPassword(const QString &pass);
  const QString &getClippedPassword();
  void reencryptPath(QString dir);
};

#endif // MAINWINDOW_H_
