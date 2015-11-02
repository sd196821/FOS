#include <QtTest>
#include <QString>
#include <QThread>
#include <QDebug>
#include "buffer.cpp"
using namespace FOS;
Q_DECLARE_METATYPE(Buffer);
Q_DECLARE_METATYPE(size_t);
Q_DECLARE_METATYPE(int*);
Q_DECLARE_METATYPE(uint8_t*);

class BufferTest : public QObject
{
    Q_OBJECT

public:
    BufferTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void BufferCaseInit();
    void BufferCaseInit_data();

    void BufferCaseLength();
    void BufferCaseLength_data();

    void BufferCaseLoopSingleReadWrite();
    void BufferCaseLoopSingleReadWrite_data();

    void BufferCaseOverLoad();
    void BufferCaseOverLoad_data();

    void BufferCaseRAM();
    void BufferCaseRAM_data();

    void BufferCaseNotRAM();
    void BufferCaseNotRAM_data();

};

BufferTest::BufferTest()
{
    int seed = QTime::currentTime().msecsSinceStartOfDay();
    qsrand(seed);
}

void BufferTest::initTestCase()
{
}
void BufferTest::cleanupTestCase()
{
    qDebug()<<sizeof(Buffer);
}

void BufferTest::BufferCaseInit()
{
    QFETCH(Buffer,buf);
    QFETCH(int,size);
    QVERIFY2(buf.getSize() == size, "Failure");
}

void BufferTest::BufferCaseLength()
{
    QFETCH(Buffer,buf);
    QFETCH(uint8_t*,data);
    QFETCH(size_t,dataLen);
    QFETCH(size_t,keep);
    int i,j,k;
    //! @note Write only
    for(i = 0; i < keep; ++i)
    {
        QVERIFY2(buf.length() == i,(QString("Len can not match.") + QString::number(i)).toLocal8Bit().data());
        QVERIFY2(buf.write(data[i]),"Fail to write");
    }
    QVERIFY2(buf.length() == i,(QString("Len can not match.") + QString::number(i)).toLocal8Bit().data());
    //! @note Read and write
    for(j = 0;i + j < dataLen; ++j)
    {
        uint8_t check;
        QVERIFY2(buf.read(check),"Fail to read");
        QVERIFY2(check == data[j],(QString("data can not match.") + QString::number(j)).toLocal8Bit().data());
        QVERIFY2(buf.write(data[i + j]),"Fail to write");
        QVERIFY2(buf.length() == i,(QString("Len can not match.") + QString::number(i + j)).toLocal8Bit().data());
    }
    //! @note Read only
    for(k = 0;buf.length() > 0;++k)
    {
        uint8_t check;
        QVERIFY2(buf.read(check),"Fail to read");
        QVERIFY2(check == data[j + k],(QString("data can not match.") + QString::number(j + k)).toLocal8Bit().data());
        QVERIFY2(buf.length() == i - k - 1,(QString("Len can not match.") + QString::number(i + j + k)+QString("but")+QString::number(buf.length())).toLocal8Bit().data());
    }
    QVERIFY2(buf.length() == 0,"not empty");
}

void BufferTest::BufferCaseLoopSingleReadWrite()
{

}

void BufferTest::BufferCaseOverLoad()
{
    QFETCH(Buffer,buf);
    QFETCH(uint8_t*,data);
    QFETCH(size_t,dataLen);
    QFETCH(size_t,bufLen);
    //! @note Check empty.
    QVERIFY2(buf.length() == 0,"Not Empty");
    //! @note Fill to full.
    int i,j,k;
    for(i = 0; i < bufLen; ++i)
        QVERIFY2(buf.write(data[i]),"Write error");
    QVERIFY2(buf.isFull(),"Not Full");
    //! @note over write.
    for(j = 0; i + j < dataLen; ++j)
        QVERIFY2(!buf.write(data[i]),"Over write note access");
    //! @note Recheck full.
    QVERIFY2(buf.isFull(),"Not Full");
    //! @note Verify data in memory.
    for(k = 0; k < bufLen; ++k)
    {
        uint8_t check;
        QVERIFY2(buf.read(check),"Fail to read");
        QVERIFY2(check == data[k],(QString("data can not match.") + QString::number(k)).toLocal8Bit().data());
    }
}

void BufferTest::BufferCaseOverLoad_data()
{
    QTest::addColumn<Buffer>("buf");
    QTest::addColumn<uint8_t*>("data");
    QTest::addColumn<size_t>("dataLen");
    QTest::addColumn<size_t>("bufLen");

    /*! @note Makeup data
     *  @attention data length should longer than buffer length,
     *  or test will occur error.
     * */
    size_t len1     = 20;
    size_t dataLen1 = 45;
    uint8_t* data1 = new uint8_t[dataLen1];
    for(int i = 0; i < dataLen1; ++i)
        data1[i] = qrand()%0x100;

    QTest::newRow("common buffer1")     <<Buffer(len1)<<data1<<dataLen1<<len1;
}

void BufferTest::BufferCaseRAM()
{
    QFETCH(Buffer,buf);
    QFETCH(size_t,bufLen);
    QFETCH(uint8_t*,data);
    QFETCH(size_t,dataLen);

    int i,j;
    uint8_t check;
    //! @note comme write.
    for(i = 0; i < bufLen; ++i)
        QVERIFY2(buf.write(data[i],i),"Fail to write.");
    QVERIFY2(buf.length() == 0,"Has effect on buffer pointer.");
    //! @note over write.
    for(j = 0; i+j < dataLen; ++j)
        QVERIFY2(!buf.write(data[i+j],i+j),"unexpected success on write.");
    QVERIFY2(buf.length() == 0,"Has effect on buffer pointer.");
    //! @note read.
    for(i = 0; i < bufLen; ++i)
    {
        QVERIFY2(buf.read(check,i),"Fail to read.");
        QVERIFY2(check ==  data[i],"Data did not match");
        //qDebug() << check;
    }
    QVERIFY2(buf.length() == 0,"Has effect on buffer pointer.");
    //! @note over read.
    check = 0x45;
    for(j = 0; i+j < dataLen; ++j)
    {
        QVERIFY2(!buf.read(check,i+j),"unexpected success on write.");
        QVERIFY2(check == 0x45,"Method has effection in unexpected position.");
    }
    QVERIFY2(buf.length() == 0,"Has effect on buffer pointer.");
}

void BufferTest::BufferCaseRAM_data()
{
    QTest::addColumn<Buffer>("buf");
    QTest::addColumn<size_t>("bufLen");
    QTest::addColumn<uint8_t*>("data");
    QTest::addColumn<size_t>("dataLen");

    //! @note Makeup data
    size_t len1     = 20;
    size_t dataLen1 = 40;
    uint8_t* data1 = new uint8_t[dataLen1];
    for(int i = 0; i < dataLen1; ++i)
        data1[i] = qrand()%0x100;

    QTest::newRow("common buffer1")     <<Buffer(len1)<<len1<<data1<<dataLen1;
}

void BufferTest::BufferCaseNotRAM()
{
    QFETCH(Buffer,buf);
    QFETCH(size_t,bufLen);
    QFETCH(uint8_t*,data);
    QFETCH(size_t,dataLen);
    QFETCH(size_t,preWrite);
    QFETCH(size_t,preRead);

    //! @note preFill
    int i,j,k;
    uint8_t check;
    for(i = 0; i < preRead; ++i)
    {
        QVERIFY2(buf.write(data[i]),"Fail to write.");
        QVERIFY2(buf.read(check),"Fail to read.");
        QVERIFY2(check == data[i],"Data is unexpected.");
    }
    for(;i < preWrite; ++i)
        QVERIFY2(buf.write(data[i]),"Fail to write.");
    QVERIFY2(buf.length() == preWrite - preRead,"unexpected length.");
    //! @note RAM fill for check;
    j = 0;
    k = 0;
    for(i = 0; i < bufLen; ++i)
    {
        if(buf.isOnHold(i))
        {QVERIFY2(buf.write(0xAA,i),"Fail to write.");j++;}
        else
        {QVERIFY2(buf.write(0x55,i),"Fail to write.");k++;}
    }
    //qDebug()<<j <<"   "<< preRead <<"   "<<preWrite<<"   "<<buf.length();
    QVERIFY2(j+k == bufLen,"Wrong buffer length.");
    QVERIFY2(j == preWrite - preRead,"Wrong on-hold length.");
    //! @note noRAM
    for(i = 0; i < bufLen; ++i)
    {
        if(i < buf.length())
            QVERIFY2(buf.read(check,i,false),"Fail to read.");
        else
            QVERIFY2(!buf.read(check,i,false),"unexepted success.");
    }
    for(i = 0; i < bufLen; ++i)
    {
        if(i < buf.getSize() - buf.length())
            QVERIFY2(buf.write(0xCC,i,false),"Fail to read.");
        else
            QVERIFY2(!buf.write(0xCC,i,false),"unexepted success.");
    }
}
void BufferTest::BufferCaseNotRAM_data()
{
    QTest::addColumn<Buffer>("buf");
    QTest::addColumn<size_t>("bufLen");
    QTest::addColumn<uint8_t*>("data");
    QTest::addColumn<size_t>("dataLen");
    QTest::addColumn<size_t>("preWrite");
    QTest::addColumn<size_t>("preRead");


    //! @note Makeup data
    size_t len1     = 20;
    size_t dataLen1 = 40;
    size_t preWrite1= 10;
    size_t preRead1 = 0;
    uint8_t* data1 = new uint8_t[dataLen1];
    for(int i = 0; i < dataLen1; ++i)
        data1[i] = qrand()%0x100;

    size_t len2     = 20;
    size_t dataLen2 = 40;
    size_t preWrite2= 30;
    size_t preRead2 = 10;
    uint8_t* data2 = new uint8_t[dataLen2];
    for(int i = 0; i < dataLen2; ++i)
        data2[i] = qrand()%0x100;

    size_t len3     = 20;
    size_t dataLen3 = 80;
    size_t preWrite3= 45;
    size_t preRead3 = 35;
    uint8_t* data3 = new uint8_t[dataLen3];
    for(int i = 0; i < dataLen3; ++i)
        data3[i] = qrand()%0x100;

    size_t len4     = 20;
    size_t dataLen4 = 40;
    size_t preWrite4= 15;
    size_t preRead4 = 5;
    uint8_t* data4 = new uint8_t[dataLen4];
    for(int i = 0; i < dataLen4; ++i)
        data4[i] = qrand()%0x100;

    QTest::newRow("common buffer1")     <<Buffer(len1)<<len1<<data1<<dataLen1<<preWrite1<<preRead1;
    QTest::newRow("common buffer2")     <<Buffer(len1)<<len2<<data2<<dataLen2<<preWrite2<<preRead2;
    QTest::newRow("common buffer3")     <<Buffer(len1)<<len3<<data3<<dataLen3<<preWrite3<<preRead3;
    QTest::newRow("common buffer4")     <<Buffer(len1)<<len4<<data4<<dataLen4<<preWrite4<<preRead4;

}

void BufferTest::BufferCaseInit_data()
{

    QTest::addColumn<Buffer>("buf");
    QTest::addColumn<int>("size");

    //! @note Makeup data
    uint8_t *buf = new uint8_t[500];

    QTest::newRow("common buffer1") <<Buffer(2)         <<int(2);
    QTest::newRow("common buffer2") <<Buffer(2048)      <<int(2048);
    QTest::newRow("common buffer2") <<Buffer(buf,500)   <<int(500);
    QTest::newRow("null buffer")    <<Buffer(0,0)       <<int(0);
    /*! @note This can not be compiled,
     *  so it can not be a test function,
     *  error would not happen.
    QTest::newRow("null buffer")    <<Buffer(0)     <<int(0);
    QTest::newRow("error")          <<Buffer(-1)    <<int(-1);
    */
}

void BufferTest::BufferCaseLength_data()
{
    QTest::addColumn<Buffer>("buf");
    QTest::addColumn<uint8_t*>("data");
    QTest::addColumn<size_t>("dataLen");
    QTest::addColumn<size_t>("bufLen");
    QTest::addColumn<size_t>("keep");

    /*! @note Makeup data
     *  @attention keep data is less than data length and buffer length,
     *  or test module will not run correctly.
     * */
    size_t Len1 = 10;
    size_t keep1 = 10;
    size_t bufLen1 = 20;
    uint8_t* data1 = new uint8_t[Len1];
    for(int i = 0; i < Len1; ++i)
        data1[i] = i;

    size_t Len2 = 65536;
    size_t keep2 = 512;
    size_t bufLen2 = 1024;
    uint8_t* data2 = new uint8_t[Len2];
    for(int i = 0; i < Len2; ++i)
        data2[i] = i;

    QTest::newRow("common buffer1")     <<Buffer(bufLen1)   <<data1    <<size_t(Len1) <<size_t(bufLen1) <<keep1;
    QTest::newRow("common cross loop")  <<Buffer(bufLen2)   <<data2    <<size_t(Len2) <<size_t(bufLen2) <<keep2;

}

void BufferTest::BufferCaseLoopSingleReadWrite_data()
{

}

QTEST_APPLESS_MAIN(BufferTest)
#include "tst_buffertest.moc"
