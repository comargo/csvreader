#include "csvreader_p.h"

CsvReaderPrivate::CsvReaderPrivate()
{
}

CsvReaderPrivate::CsvReaderPrivate(const QString &data)
    : fileData(data)
{
}

void CsvReaderPrivate::init(CsvReader *q)
{
    q_ptr = q;
}

bool CsvReaderPrivate::parse()
{

    npos = 0;
    int total = fileData.size();
    State state = RowStart;
    while(npos < total) {
        QChar ch = fileData.at(npos);
        switch (state) {
        case CsvReaderPrivate::RowStart:
            if(ch != QChar('\r')
                    && ch != QChar('\n')) {
                parsedData.append(QStringList());
                state = FieldStart;
            }
            else {
                // Eat CR and LF
                ++npos;
            }
            break;
        case CsvReaderPrivate::FieldStart:
            parsedData.last().append(QString());
            if(ch == QChar('"')) {
                state = FieldDQuoted;
                ++npos; // eat DQoute
            } else {
                state = FieldUnqouted;
            }
            break;
        case CsvReaderPrivate::FieldUnqouted:
            if(ch == QChar(',')) {
                state = FieldStart;
                ++npos; //eat comma
            } else if(ch == QChar('\r')
                      || ch == QChar('\n')){
                state = RowStart;
                ++npos;
            } else {
                parsedData.last().last().append(ch);
                ++npos;
            }
            break;
        case CsvReaderPrivate::FieldDQuoted:
            if(ch == QChar('"')) {
                state = FieldDQuotedDQuote;
                ++npos; // eat DQuote
            } else {
                parsedData.last().last().append(ch);
                ++npos;
            }
            break;
        case CsvReaderPrivate::FieldDQuotedDQuote:
            if(ch == QChar(',')) {
                state = FieldStart;
                ++npos; //eat comma
            } else if(ch == QChar('\r')
                      || ch == QChar('\n')){
                state = RowStart;
                ++npos;
            } else if(ch == QChar('"')) {
                state = FieldDQuoted;
                parsedData.last().last().append(ch);
                ++npos;
            } else {
                state = Error;
            }
            break;
        case CsvReaderPrivate::Error:
            return false;
            break;
        }
    }
    return true;
}
