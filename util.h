#ifndef UTIL_H_
#define UTIL_H_

#include <QProcessEnvironment>
#include <QString>
#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
#include <QRandomGenerator>
#else
#include <fcntl.h>
#include <unistd.h>
#endif
#include <cassert>

/*!
    \class Util
    \brief Some static utilities to be used elsewhere.
 */
class Util {
public:
  static QString findBinaryInPath(QString binary);
  static QString findPasswordStore();
  static QString normalizeFolderPath(QString path);
  static bool checkConfig(QString passStore, QString passExecutable,
                          QString gpgExecutable);
  static void qSleep(int ms);
  static QString generateRandomPassword(const QString &charset, unsigned int length);
  static quint32 boundedRandom(quint32 bound);

private:
  static void initialiseEnvironment();
  static QProcessEnvironment _env;
  static bool _envInitialised;
};

#endif // UTIL_H_
