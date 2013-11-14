#include <QString>
#include <QtTest>

#include <csvreader.h>

namespace QTest {
template<class T>
bool qCompare(QList<T> const &t1, QList<T> const &t2, const char *actual, const char *expected, const char *file, int line)
{
    if(!qCompare(t1.size(), t2.size()
                 , qPrintable(QLatin1String(actual)+QLatin1String(".size"))
                 , qPrintable(QLatin1String(expected)+QLatin1String(".size"))
                 , file, line))
        return false;
    for(int i=0; i<t1.size(); ++i) {
        if(!qCompare(t1[i], t2[i]
                     , qPrintable(QString(actual)+QString("[%1]").arg(i))
                     , qPrintable(QString(expected)+QString("[%1]").arg(i))
                     , file, line))
            return false;
    }
    return true;
}
}

class CvsReaderTest : public QObject
{
    Q_OBJECT

public:
    CvsReaderTest();

private Q_SLOTS:
    void testCase1();
};

CvsReaderTest::CvsReaderTest()
{
}

void CvsReaderTest::testCase1()
{
    QStringList dataList;
    dataList << "1,2"
             << "\"1\",\"2\""
             << "\"1,2\",3"
             << "1 2,3"
             << "\"1\r\n2\",3";
    QList<QStringList> expectedData;
    expectedData.append(QStringList());
    expectedData.last() << "1"
                        << "2";
    expectedData.append(QStringList());
    expectedData.last() << "1"
                        << "2";
    expectedData.append(QStringList());
    expectedData.last() << "1,2"
                        << "3";
    expectedData.append(QStringList());
    expectedData.last() << "1 2"
                        << "3";
    expectedData.append(QStringList());
    expectedData.last() << "1\r\n2"
                        << "3";
    QList<QStringList> parsedData = CsvReader::parse(dataList.join("\r\n"));
    QCOMPARE(parsedData, expectedData);
}

QTEST_APPLESS_MAIN(CvsReaderTest)

#include "tst_cvsreadertest.moc"
