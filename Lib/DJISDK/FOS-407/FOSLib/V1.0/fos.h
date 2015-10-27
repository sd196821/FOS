/*! @abstract ******************************************************************
 *  @version 0.1
 *  @corelib FOSLib
 *
 *  @brief
 *  @chapter Syetem model
 *
 *  @chapter Node model
 *  In a FOS-Node, it seems like a common Turing machine.
 *  Every node has a stream buffer.
 *  The buffer supply swquential and random read and write.
 *
 *  @attention
 *  ****************************************** Copyright (c) ******************************************
 *  @author: William Wu
 *  @e-mail: FOS@justwillim.com
 *  @date  : 2015-08-25
 *  ****************************************** Copyright (c) ******************************************/
#ifndef FOS_H
#define FOS_H
#include <stdint.h>

namespace FOS
{
typedef unsigned long long ID;
typedef uint64_t Time;
class Node;
class TaskHost;


/*! @note Quick dynamic node linked-list
 *  @brief Quick dynamic node linked-list
 *  provide a way to store node's pointer dynamically and quickly.
 * */
typedef struct NodeListStruct
{
    Node** list;
    size_t amount;
    NodeListStruct* next;
}NodeList;
static const size_t nodeListBaseSize = 64;

typedef struct
{
    Node* node;
    size_t pos;
    size_t len;
}LinkList;
typedef struct NodeStructure
{
    LinkList*   from;
    size_t      fromNumber;
    LinkList*   to;
    size_t      toNumber;
    LinkList*   children;
    size_t      childrenNumber;
}NodeMem;

namespace NodeType
{
enum is
{
    Linker,
    Sensor,
    Actuator,
    Encoder,
    Decoder,
    Exhibitor
};
}


class Buffer
{
public:
    Buffer(size_t Size);
#ifdef STATIC_MEMORY
    Buffer(uint8_t* Memory, size_t Size);
#endif //STATIC_MEMORY
private:
    void init(uint8_t* Memory, size_t Size);
public:
    bool write(uint8_t &data);
    bool read (uint8_t &data);
    bool read (uint8_t &data,size_t pos,bool holdBuff = true);
    bool write(uint8_t &data,size_t pos,bool holdBuff = true);
    void flush(size_t len);
    //! @note Auto in line, you should check your asm code to verify this feature.
    bool isEmpty(){return ((readFrom == writeTo)&&writeable);}
    //! @note Auto in line, you should check your asm code to verify this feature.
    bool isFull() {return ((readFrom == writeTo)&&readable );}
    size_t length();
    size_t getSize(){return size;}
public:
    void exchangeMemory(Buffer *with);
    void exchangeMemory(uint8_t *with,size_t Size);
private:
    volatile uint8_t *memory;
    volatile bool readable;
    volatile bool writeable;
    size_t size;
    volatile size_t readFrom;
    volatile size_t writeTo;
};

class Node
{
public:
    Node();
private:
    virtual void initNode();
public:
    //! @chapter Basic I/O
    bool read (uint8_t &data);
    bool write(uint8_t &data);
    size_t read (uint8_t *stream,size_t len);
    size_t write(uint8_t *stream,size_t len);
    bool read (uint8_t &data,size_t pos,bool holdBuff = true);
    bool write(uint8_t &data, size_t pos,bool holdBuff = true);
    size_t read (uint8_t *stream, size_t pos, size_t len);
    size_t write(uint8_t *stream, size_t pos, size_t len);
public:
    //! @chapter Link
    bool linkTo(Node* to,size_t dataPos,size_t len);
    bool dislink(Node* with);
    bool addChild(Node* child,size_t dataPos,size_t len);
    bool removeChild(Node* child,size_t dataPos,size_t len);
private:
    NodeList *fromNodes;
    NodeList *toNodes;
    NodeList *children;
    NodeList *parents;
public:
    //! @chapter network operation
    bool isSelfLoop();
    bool isRecurrence();
    bool hasLoop();
    virtual void pollNode();
    virtual void pollChildren();
    virtual void pollSelf();

public:
    //! @chapter Data stream
    virtual bool importData(uint8_t *cmd = 0,size_t len = 0);
    virtual bool exportData(uint8_t *cmd = 0,size_t len = 0);
    virtual bool encode();  //! @note from data to send.
    virtual bool decode();  //! @note from recv to data.
    virtual void send();    //! @note Post data.
    virtual void recv();    //! @note Get data.
public:
    //! @chapter Multitask
    virtual void run();
    void regist(Time Ticks = 0,Time Session = 0);
    void start() {access = true; }
    void pause() {access = false;}
public:
    static void init();
    static void pollTasks();
private:
    static void saveError();
    static void loadError();
private:
    Time ticks;
    Time period;
    Time session;
    bool access;
public:
    //! @chapter NVM I/O
    void save();
    void load();
private:
    virtual bool saveByte(uint8_t &data,size_t add);
    virtual bool loadByte(uint8_t &data,size_t add);
    size_t saveBytes(uint8_t *data,size_t len,size_t add);
    size_t loadBytes(uint8_t *data,size_t len,size_t add);
private:
    ID id;
    NodeType::is type;
    NodeMem *memory;
    Buffer  *recvBuf;
    Buffer  *sendBuf;
    Buffer  *dataBuf;
};


}

#endif // FOS_H
