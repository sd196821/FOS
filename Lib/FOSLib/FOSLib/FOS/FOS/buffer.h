/*! @abstract ******************************************************************
 *  @version 2.3
 *  @corelib FOSCore
 *
 *  @brief
 *  @chapter Syetem model
 *  Class Buffer provide a muliti functional buffer,
 *  It offers Looped-Linear Access Memory(LLAM) and Random Access Memory(RAM)
 *  two basic mode to operat data.
 *
 *  As a LLAM, if you choose it as a dynamic memory and it has dynamic access,
 *  it will be a infinit LLM,
 *  and it will manage its memory size automatically.
 *  Or it will be a normal LLM.
 *
 *  As a RAM, if you choose not to hold the buffer, it will be a Mixed Access Memory(MAM),
 *  this feature gives a easy way to access data, when you use it as a LLAM,
 *  and wanted to verify some data, without distroy the storage structure in LLAM.
 *  @attention
 *  If you are not really know what you a doing exactly,
 *  please use just it as a one modeled memory to storage data.
 *  Especially, use MAM and RAM in a same buffer.
 *
 *  Cotinually expand buffer's memory will cause temporally memory abuse.
 *  Do not ues this feature to expand a RAM-modeled buffer.
 *  Or you should be really carefully to maintenance the RAM's storage structure integrity.
 *
 *  Any memory hack should be forbidden. Ping pong it if you really want to do so.
 *  See function: void exchange(uint8_t* with,size_t Size);
 *
 *  A buffer will forbidden dynamic fuctions when it was alloced from an other buffer.
 *  Do not try to use dynamic operations anytime anyway, when it was alloced from another.
 *
 *  @attention
 *  Optional definitions:
 *  STATIC_MEMORY
 *      Cut down the dynamic memory module.
 *  NO_OPTIMIZE
 *      Cut down the statistical optimize part.
 *      @attention Optimize needs dynamic memory,
 *      so definition STATIC_MEMORY will also cut down this module.
 *  NO_ACCESS
 *      Cut down the access module.
 *  NON_ALLOC_BUFFER
 *      Cut down the alloc module.
 *
 *  @version features:
 *  -V2.3
 *  -* Add Buffer's host Buffer
 *   * Prepare to alloc Buffer to an other buffer.
 *  -* Prepare to add statistical optimize.
 *  -* Set access module not using as default.
 *   * When you need a access module,
 *   * it means you are trying to working a huge system out,
 *   * or you are debugging.
 *   * Use it when you really need to do so.
 *   * Or there will be a lot of space or time abuse.
 *  -* Pause access module empolder.
 *   * @todo Restart at version 3.0 or later.
 *  -V2.2
 *  -* Add muliti data access.
 *  -* Split Dynamic memory and Access part
 *   * Give a way to cut down some redundant feature.
 *  -V2.1
 *  -* Add MAM model
 *  -V2.0
 *  -* Add RAM model
 *  -* Add Test Unit
 *  -V1.0
 *  -* LLAM
 *
 *  ****************************************** Copyright (c) ******************************************
 *  @author: William Wu
 *  @e-mail: FOS@justwillim.com
 *  @date  : 2015-09-04
 *  ****************************************** Copyright (c) ******************************************/

#ifndef BUFFER_H
#define BUFFER_H

#include "FOSCore.h"
#define NO_ACCESS
#pragma pack(1)
namespace FOS
{
namespace BufferDef
{
#ifndef NO_ACCESS
enum Access
{
    NoAccess        = 0,//0x00,0b00000000
    ReadAccess      = 1,//0x01,0b00000001
    WriteAccess     = 2,//0x02,0b00000010
    ReadWriteAccess = 3,//0x03,0b00000011
    DynamicAccess   = 4,//0x04,0b00000100
    FullAccess      = 7,//0x07,0b00000111
};
#endif// NO_ACCESS
}// namespace BufferDef

class Buffer
{
public:
    Buffer(uint8_t *Memory = 0, size_t Size = 0);
#ifndef STATIC_MEMORY
    Buffer(size_t Size,Buffer* allocFrom = 0);
#endif // STATIC_MEMORY
private:
    void init(uint8_t *Memory, size_t Size);
public:
    //! @chapter Basic I/O
    bool   write(uint8_t data);
    bool   read(uint8_t &data);
    size_t write(uint8_t *data,size_t len);//! @todo optimize
    size_t read (uint8_t *data,size_t len);//! @todo optimize

    /*! @note Random read and write. Time Complexity O(1).
     *  @note When asRAM is true,it means read and write will not consider pointer readFrom and writeTo's position.
     *  When it is false,it means read and write pointer offset will pluse pointer readFrom or writeTo.
     *  Whatever which mod were choosen, it will not change pointer readFrom and writeTo's position.
     *  @attention If you choose asRAM mod is false, these I/O method will not modify on-hold data.
     *  Or these I/O method will modify any data in buffer's range.
     *
     *  @note Typical data structre:
     *  |-------------++++++++++++++++--------------|
     *  S-------------R---------------W-------------E
     *  SU-----------UH--------------HU------------UE
     *
     *
     *  |+++++++++++++----------------++++++++++++++|
     *  S-------------W---------------R-------------E
     *  SU-----------HU--------------UH------------UE
     *
     *  S:start
     *  R:readFrom pointer
     *  W:writeTo pointer
     *  E:end
     *  U:unhold data
     *  H:on-hold data
     * */
    bool   write(uint8_t data,size_t pos,bool asRAM = true);
    bool   read(uint8_t &data,size_t pos,bool asRAM = true);
    size_t write(uint8_t *data,size_t pos,size_t len,bool asRAM = true);//! @todo optimize.
    size_t read (uint8_t *data,size_t pos,size_t len,bool asRAM = true);//! @todo optimize.
public:
    /*! @chapter Buffer operations
     *  @attention Need to check Auto inline from asm code.
     * */
    bool isReadable() const {return readable;}
    bool isWriteable()const {return writeable;}
    bool isEmpty() const {return ((readFrom == writeTo)&&isWriteable());}
    bool isFull()  const {return ((readFrom == writeTo)&&isReadable() );}
    size_t length() const;
    size_t getSize()const {return size;}
    bool isOnHold(size_t pos);//! @note inline function. Needs to check asm code.
    void flush(size_t len = 0);
    /*! @note About method exchange.
     *  Method exchange, is used for ping pong data transfer.
     *  When you decide to make an exchange,
     *  it means data in current buffer will has no relationship with it any longer.
     *  Exchange with a Buffer,
     *  the readFrom and writeTo pointer will be exchanged together.
     *  Exchange with a memory pointer,
     *  the buffer will abandon pointer readFrom and writeTo.
     * */
    void exchange(Buffer *with);
    void exchange(uint8_t *with,size_t Size);
private:
    volatile bool readable :1;
    volatile bool writeable:1;
    volatile uint8_t* memory;
    size_t size;
    volatile size_t readFrom;
    volatile size_t writeTo;
#ifndef STATIC_MEMORY
public:
    //! @chapter Dynamic storage
    //! @todo Actrualize

private:
    volatile Buffer* dynamic;
#endif // STATIC_MEMORY
#ifndef NO_ACCESS
public:
    //! @chapter Access
    //! @todo Acturalize
    BufferDef::Access getAccess() const {return access;}
    void setAccess(const BufferDef::Access &value){access = value;}
private:
    BufferDef::Access access;
    void* readAccess;
    void* writeAccess;
#endif// NO_ACESS
#ifndef NON_ALLOC_BUFFER
public:
    //! @chapter Alloc buffer.
    //! @todo Acturalize
    void* push(size_t size);
    bool  pop (size_t size);
    //    bool allocTo  (Buffer* buffer,size_t Size,size_t start = 0);
    //    bool allocFrom(Buffer* buffer,size_t Size,size_t start = 0);
private:
    Buffer *host;
    size_t usedHeap;
#endif// NON_ALLOC_BUFFER
};
#pragma pack()
}// namespace FOS

#endif // BUFFER_H
