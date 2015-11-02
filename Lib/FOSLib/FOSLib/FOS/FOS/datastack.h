#ifndef DATASTACK_H
#define DATASTACK_H
#include "buffer.h"
namespace FOS
{
class DataStack
{
public:
    DataStack(void* StackType = 0,Buffer *Recv = 0,Buffer *Send = 0);
private:
    virtual void init();
public:
    bool read(uint8_t &data){return recvBuf->read(data);}
    bool write(uint8_t data){return sendBuf->write(data);}

    size_t read (uint8_t *data, size_t len){return recvBuf->read(data,len);}
    size_t write(uint8_t *data, size_t len){return sendBuf->write(data,len);}

    bool read(uint8_t &data, size_t pos, bool isRAM = true){return recvBuf->read(data,pos,isRAM);}
    bool write(uint8_t data, size_t pos, bool isRAM = true){return sendBuf->write(data,pos,isRAM);}

    size_t read (uint8_t *data, size_t len, size_t pos, bool isRAM = true)
    {return recvBuf->read(data,len,pos,isRAM);}
    size_t write(uint8_t *data, size_t len, size_t pos, bool isRAM = true)
    {return sendBuf->write(data,len,pos,isRAM);}

public:
    virtual bool readNow(uint8_t &data);
    virtual bool writeNow(uint8_t data);

    virtual size_t readNow (uint8_t *data, size_t len);
    virtual size_t writeNow(uint8_t *data, size_t len);

    virtual bool readNow(uint8_t &data, size_t pos, bool isRAM = true);
    virtual bool writeNow(uint8_t data, size_t pos, bool isRAM = true);

    virtual size_t readNow (uint8_t *data, size_t len, size_t pos, bool isRAM = true);
    virtual size_t writeNow(uint8_t *data, size_t len, size_t pos, bool isRAM = true);

protected:
    virtual void poll();
    virtual void pollRead();
    virtual void pollWrite();
public:
    void *getStackType() const {return stackType;}
    void setStackType(void *value) {stackType = value;}
    Buffer *getRecvBuf() const {return recvBuf;}
    void setRecvBuf(Buffer *value) {recvBuf = value;}
    Buffer *getSendBuf() const {return sendBuf;}
    void setSendBuf(Buffer *value) {sendBuf = value;}
    bool getSending() const {return sending;}
    void setSending(bool value) {sending = value;}
    bool getRecving() const {return recving;}
    void setRecving(bool value) {recving = value;}
    Buffer *getMappingBuf() const {return mappingBuf;}
    void setMappingBuf(Buffer *value) {mappingBuf = value;}

private:
    void *stackType;
    Buffer *mappingBuf;
    Buffer *recvBuf;
    Buffer *sendBuf;
    bool sending;
    bool recving;
};

}

#endif // DATASTACK_H
