#ifndef CSVREADER_H
#define CSVREADER_H

#include <QtGlobal>

QT_BEGIN_NAMESPACE
class QString;
class QStringList;
template<class T> class QList;
class QIODevice;
QT_END_NAMESPACE

#include <QChar>

namespace CSVReader {

enum class CSVQuotes { Auto, Always };

QList<QStringList> fromCSV(const QString &data, const QChar &delimeter = QLatin1Char(','));
QList<QStringList> fromCSV(QByteArray data, const QChar &delimeter = QLatin1Char(','));
QList<QStringList> fromCSV(QIODevice *device, const QChar &delimeter = QLatin1Char(','));

QString toCSV(const QList<QStringList> &data, const QChar &delimeter = QLatin1Char(','), CSVQuotes quotes = CSVQuotes::Auto);

}


#endif // CSVREADER_H
