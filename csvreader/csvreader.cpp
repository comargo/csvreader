#include "csvreader.h"

#include <QBuffer>
#include <QList>
#include <QRegularExpression>
#include <QStringList>

#include <QtDebug>

struct CSVStateMachine
{
    enum CSVState {
        LineStart,
        FieldStart,
        FieldRegular,
        FieldQuoted,
        FieldEnd,
        LineEnd,
        Stop
    };

    CSVStateMachine(QIODevice *device, QChar delimiter)
        : device(device)
        , delimiter(delimiter)
        , state(CSVState::LineStart)
    {}

    QIODevice *device;
    QChar delimiter;
    CSVState state;
    QStringList row;
    QByteArray field;

    void microstep()
    {
        state = _microstep();
    }
private:
    CSVState _microstep();
};

CSVStateMachine::CSVState CSVStateMachine::_microstep()
{
    char ch = 0;
    switch (state) {
    case LineStart:
        if(device->peek(&ch, 1) < 1 ||
                ch == '\r' || ch == '\n') {
            return LineEnd;
        }
        // Other character - new field
        return FieldStart;

    case FieldStart:
        if(device->peek(&ch, 1) < 1) {
            return FieldEnd;
        }
        if(ch == '"') {
            device->getChar(&ch);
            return FieldQuoted;
        }
        return FieldRegular;

    case FieldRegular:
        if(device->peek(&ch, 1) < 1 ||
                ch == '\r' || ch == '\n' || ch == delimiter) {
            return FieldEnd;
        }
        device->getChar(&ch);
        field.push_back(ch);
        return FieldRegular;

    case FieldQuoted:
        if(!device->getChar(&ch)) {
            return FieldEnd;
        }
        if(ch == '"') {
            ch = 0;
            if(device->peek(&ch, 1) < 1 ||
                    ch == '\r' || ch == '\n' || ch == delimiter ) {
                return FieldEnd;
            }
            if(ch == '"') { // 2DQUOTE
                device->getChar(&ch);
                field.push_back(ch);
                return FieldQuoted;
            }
        }
        field.push_back(ch);
        return FieldQuoted;

    case FieldEnd:
        row.push_back(field);
        field.clear();
        if(device->peek(&ch, 1) < 1 ||
                ch == '\r' || ch == '\n') {
            return LineEnd;
        }
        device->getChar(&ch);
        return FieldStart;

    case LineEnd:
        if(device->getChar(&ch)) {
            if(ch == '\r') {
                ch = 0;
                if(device->peek(&ch, 1) > 0 && ch == '\n') {
                    device->getChar(&ch);
                }
            }
        }
        return Stop;
    }

    Q_ASSERT(false);
    return Stop;

}

static QStringList fromCSVRow(QIODevice *device, QChar delimiter)
{
    CSVStateMachine machine(device, delimiter);

    while(machine.state != CSVStateMachine::Stop) {
        machine.microstep();
    }
    return machine.row;
}

QList<QStringList> CSVReader::fromCSV(const QString &data, const QChar &delimeter)
{
    return fromCSV(data.toUtf8(), delimeter);
}

QList<QStringList> CSVReader::fromCSV(QByteArray data, const QChar &delimeter)
{
    QBuffer buffer(&data);
    buffer.open(QIODevice::ReadOnly);
    return fromCSV(&buffer, delimeter);
}

QList<QStringList> CSVReader::fromCSV(QIODevice *device, const QChar &delimeter)
{
    QList<QStringList> result;
    while(!device->atEnd()) {
        result.push_back(fromCSVRow(device, delimeter));
    }
    return result;
}

static QString quoteString(QString in)
{
    QString out;
    out.push_back('"');
    foreach (QChar ch, in) {
        if(ch == '"') {
            out.push_back('"');
        }
        out.push_back(ch);
    }
    out.push_back('"');
    return out;
}

static bool needQuotes(const QString &field, const QChar &delimiter, CSVReader::CSVQuotes quotes)
{
    if(quotes == CSVReader::CSVQuotes::Always)
        return true;
    foreach (const QChar &ch, field) {
        if(ch == delimiter ||
                ch == '"' || ch == '\r' || ch == '\n') {
            return true;
        }
    }
    return false;
}

QString CSVReader::toCSV(const QList<QStringList> &data, const QChar &delimeter, CSVReader::CSVQuotes quotes)
{
    QString result;
    foreach (const QStringList &row, data) {
        bool firstField = true;
        foreach (const QString &field, row) {
            if(firstField) {
                firstField = false;
            }
            else {
                result.append(',');
            }
            result.append(needQuotes(field, delimeter, quotes)?quoteString(field):field);
        }
        result.append('\n');
    }
    return result;
}
