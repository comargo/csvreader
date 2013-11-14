#ifndef CSVREADER_H
#define CSVREADER_H

#include "csvreader_global.h"

#include <QObject>
#include <QStringList>

class CsvReaderPrivate;
class CSVREADERSHARED_EXPORT CsvReader : public QObject {
    Q_OBJECT
public:
    explicit CsvReader(QObject *parent = 0);
    CsvReader(const QString &data, QObject *parent = 0);
    ~CsvReader();

public:
    static QList<QStringList> parse(const QString &data);

public:
    QString data() const;
    QList<QStringList> parsedData() const;

public Q_SLOTS:
    bool parse();
    void setData(const QString &data);



private:
    Q_DECLARE_PRIVATE(CsvReader)
    CsvReaderPrivate* d_ptr;
    Q_DISABLE_COPY(CsvReader)
};

#endif // CSVREADER_H
