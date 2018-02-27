#include <QString>
#include <QtTest>

#include <csvreader.h>

Q_DECLARE_METATYPE(CSVReader::CSVQuotes)

class CvsReaderTest : public QObject
{
    Q_OBJECT

public:
    CvsReaderTest();

private Q_SLOTS:
    void fromCSV_data();
    void fromCSV();
    void toCSV_data();
    void toCSV();
};

CvsReaderTest::CvsReaderTest()
{
}

void CvsReaderTest::fromCSV_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<QChar>("delimiter");
    QTest::addColumn<QList<QStringList>>("result");

    QTest::newRow("simple one row") << "1,2" << QChar(',') << QList<QStringList>{{"1","2"}};
    QTest::newRow("simple two rows") << "1,2\n3,4" << QChar(',') << QList<QStringList>{{"1","2"},{"3","4"}};
    QTest::newRow("quoted with comma") << "1,\"2,3\"" << QChar(',') << QList<QStringList>{{"1","2,3"}};
    QTest::newRow("quoted with quote") << "1,\"2 \"\"3\"\" 4\"" << QChar(',') << QList<QStringList>{{"1", "2 \"3\" 4"}};
    QTest::newRow("quoted with CRLF") << "1,\"2\n3\"" << QChar(',') << QList<QStringList>{{"1", "2\n3"}};
    QTest::newRow("empty field") << "1,,2" << QChar(',') << QList<QStringList>{{"1",QString(),"2"}};
    QTest::newRow("empty quoted field") << "1,\"\",2" << QChar(',') <<QList<QStringList>{{"1",QString(),"2"}};
    QTest::newRow("two empty lines") << "\n\n" << QChar(',') << QList<QStringList>{{},{}};
    QTest::newRow("national alphabet") << "Hello,Привет,你好" << QChar(',') << QList<QStringList>{{"Hello","Привет","你好"}};
}

void CvsReaderTest::fromCSV()
{
    QFETCH(QString, string);
    QFETCH(QChar, delimiter);
    QFETCH(QList<QStringList>, result);
    QCOMPARE(CSVReader::fromCSV(string, delimiter), result);
}

void CvsReaderTest::toCSV_data()
{
    QTest::addColumn<QList<QStringList>>("data");
    QTest::addColumn<QChar>("delimiter");
    QTest::addColumn<CSVReader::CSVQuotes>("quotes");
    QTest::addColumn<QString>("result");

    QTest::newRow("simple one row AUTO")
            << QList<QStringList>{{"1","2"}}
            << QChar(',')
            << CSVReader::CSVQuotes::Auto
            << "1,2\n"
               ;
    QTest::newRow("simple two rows AUTO")
            << QList<QStringList>{{"1","2"},{"3","4"}}
            << QChar(',')
            << CSVReader::CSVQuotes::Auto
            << "1,2\n3,4\n"
               ;
    QTest::newRow("quoted with comma AUTO")
            << QList<QStringList>{{"1","2,3"}}
            << QChar(',')
            << CSVReader::CSVQuotes::Auto
            << "1,\"2,3\"\n"
               ;
    QTest::newRow("quoted with quote AUTO")
            << QList<QStringList>{{"1", "2 \"3\" 4"}}
            << QChar(',')
            << CSVReader::CSVQuotes::Auto
            << "1,\"2 \"\"3\"\" 4\"\n"
               ;
    QTest::newRow("quoted with CRLF AUTO")
            << QList<QStringList>{{"1", "2\n3"}}
            << QChar(',')
            << CSVReader::CSVQuotes::Auto
            << "1,\"2\n3\"\n"
               ;
    QTest::newRow("empty field AUTO")
            << QList<QStringList>{{"1",QString(),"2"}}
            << QChar(',')
            << CSVReader::CSVQuotes::Auto
            << "1,,2\n"
               ;
    QTest::newRow("two empty lines AUTO")
            << QList<QStringList>{{},{}}
            << QChar(',')
            << CSVReader::CSVQuotes::Auto
            << "\n\n"
               ;

    QTest::newRow("simple one row ALWAYS")
            << QList<QStringList>{{"1","2"}}
            << QChar(',')
            << CSVReader::CSVQuotes::Always
            << "\"1\",\"2\"\n"
               ;
    QTest::newRow("simple two rows ALWAYS")
            << QList<QStringList>{{"1","2"},{"3","4"}}
            << QChar(',')
            << CSVReader::CSVQuotes::Always
            << "\"1\",\"2\"\n\"3\",\"4\"\n"
               ;
    QTest::newRow("quoted with comma ALWAYS")
            << QList<QStringList>{{"1","2,3"}}
            << QChar(',')
            << CSVReader::CSVQuotes::Always
            << "\"1\",\"2,3\"\n"
               ;
    QTest::newRow("quoted with quote ALWAYS")
            << QList<QStringList>{{"1", "2 \"3\" 4"}}
            << QChar(',')
            << CSVReader::CSVQuotes::Always
            << "\"1\",\"2 \"\"3\"\" 4\"\n"
               ;
    QTest::newRow("quoted with CRLF ALWAYS")
            << QList<QStringList>{{"1", "2\n3"}}
            << QChar(',')
            << CSVReader::CSVQuotes::Always
            << "\"1\",\"2\n3\"\n"
               ;
    QTest::newRow("empty field ALWAYS")
            << QList<QStringList>{{"1",QString(),"2"}}
            << QChar(',')
            << CSVReader::CSVQuotes::Always
            << "\"1\",\"\",\"2\"\n"
               ;
    QTest::newRow("two empty lines ALWAYS")
            << QList<QStringList>{{},{}}
            << QChar(',')
            << CSVReader::CSVQuotes::Always
            << "\n\n"
               ;
}

void CvsReaderTest::toCSV()
{
    QFETCH(QList<QStringList>, data);
    QFETCH(QChar, delimiter);
    QFETCH(CSVReader::CSVQuotes, quotes);
    QFETCH(QString, result);
    QCOMPARE(CSVReader::toCSV(data, delimiter, quotes), result);
}

QTEST_APPLESS_MAIN(CvsReaderTest)

#include "tst_cvsreadertest.moc"
