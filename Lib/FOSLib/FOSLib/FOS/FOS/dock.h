/*! @abstract ******************************************************************
 *  @version 0.1
 *  @corelib FOSCore
 *
 *  @brief
 *  @chapter Syetem model
 *  Dock is the basic class for Forest Operating System(FOS),
 *  which host a tree, and link them as a forest in different data stak.
 *
 *  As a operating system, Dock will sacrifice some efficiency,
 *  it is mainly be wasted in virtual table.
 *  Fortunately, virtual table's efficiency has not difference with C-like hook.
 *  So, please do not be entangled with virtual.
 *  It is not such tardy as you think.
 *
 *  @attention
 *  Optional definitions:
 *
 *  @version features:
 *  -V0.1
 *  -* Construct the main structure.
 *
 *  ****************************************** Copyright (c) ******************************************
 *  @author: William Wu
 *  @e-mail: FOS@justwillim.com
 *  @date  : 2015-09-05
 *  ****************************************** Copyright (c) ******************************************/
#ifndef DOCK_H
#define DOCK_H

#include "datastack.h"
#include "linker.h"

namespace FOS
{
typedef uint64_t        ID;
typedef List<DataStack*> StackList;
typedef List<Dock*> DockList;

class Dock
{
public:  
    Dock(size_t bufferSize = 0);
private:
    virtual void init();
    bool allocMapping(DataStack* stack,size_t size);
public:
    //! @chapter Dock operations
    virtual void poll();

    /*
public:
    //! @chapter Operations between docks.
    Linker* linkTo(Dock* dock);
    bool hasLinkTo(Dock* dock);
    Linker* linkFrom(Dock* dock);
    bool hasLinkFrom(Dock* dock);
    */

public:
    //! @chapter Non-Volatile Memory(NVM) I/O
    virtual bool save();
    virtual bool load();

public:
    //! @chapter Underlying data operational interface
    StackList *getStackList() const {return stackList;}
    void setStackList(StackList *value) {stackList = value;}

    LinkerList *getLinkerList() const {return linkerList;}
    void setLinkerList(LinkerList *value) {linkerList = value;}

    DockList *getSubDockList() const {return subDockList;}
    void setSubDockList(DockList *value) {subDockList = value;}

    Buffer *getBuffer() const {return buffer;}
    void setBuffer(Buffer *value) {buffer = value;}

private:
    ID id;
    Buffer     *buffer;
    StackList  *stackList;
    LinkerList *linkerList;
    DockList   *subDockList;
};
}
#endif // DOCK_H
