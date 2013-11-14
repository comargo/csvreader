#ifndef CSVREADER_P_H
#define CSVREADER_P_H

#include "csvreader.h"

class CsvReaderPrivate
{
public:
    enum State {
        RowStart
        , FieldStart
        , FieldUnqouted
        , FieldDQuoted
        , FieldDQuotedDQuote
        , Error
    };

    CsvReaderPrivate();
    CsvReaderPrivate(const QString &data);

    void init(CsvReader *q);

    bool parse();

    QString fileData;
    int npos;
    QList<QStringList> parsedData;

    CsvReader *q_ptr;
    Q_DECLARE_PUBLIC(CsvReader)

};

#endif // CSVREADER_P_H
