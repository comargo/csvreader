#include "csvreader.h"
#include "csvreader_p.h"

#include <QTextStream>

CsvReader::CsvReader(QObject *parent)
    : QObject(parent)
    , d_ptr(new CsvReaderPrivate)
{
    d_func()->init(this);
}

CsvReader::CsvReader(const QString &data, QObject *parent)
    : QObject(parent)
    , d_ptr(new CsvReaderPrivate(data))
{
    d_func()->init(this);
}

CsvReader::~CsvReader()
{
    delete d_ptr;
}

QList<QStringList> CsvReader::parse(const QString &data)
{
    CsvReader reader(data);
    if(!reader.parse())
        return QList<QStringList>();
    return reader.parsedData();
}

void CsvReader::setData(const QString &data)
{
    d_func()->parsedData.clear();
    d_func()->fileData = data;
}

QString CsvReader::data() const
{
    return d_func()->fileData;
}

QList<QStringList> CsvReader::parsedData() const
{
    return d_func()->parsedData;
}

bool CsvReader::parse()
{
    return d_func()->parse();
}
