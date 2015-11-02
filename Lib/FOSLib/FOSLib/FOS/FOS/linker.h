/*! @abstract ******************************************************************
 *  @version 0.1
 *  @corelib FOSCore
 *
 *  @brief
 *  @chapter Syetem model
 *  Linker is the basic class for Forest Operating System (FOS),
 *  which provide to link docks to a mulitiable graph (a forest as usual).
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
#ifndef LINKER_H
/*! @abstract ******************************************************************
 *  @version 0.1
 *  @corelib FOSCore
 *
 *  @brief
 *  @chapter Syetem model
 *  Linker is a double-layered tree structure,
 *  which can link form a @class Dock to other Docks.
 *  It offers a way to transform data stream from a dock to another.
 *  And also a basic structure for dock's network and graph convert.
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
 *  @date  : 2015-09-07
 *  ****************************************** Copyright (c) ******************************************/
#define LINKER_H

#include "FOSCore.h"
#include "list.h"
#include "buffer.h"

namespace FOS
{
class Dock;
class Linker;
typedef List<Linker*>    LinkerList;
typedef struct
{
    LinkerList* linkerList;
    void        *data;
    size_t      size;
} StreamList;
class Linker
{
public:
    Linker();
private:
    virtual void init();
public:
    bool exportTo(Linker* linker);
    void dockTo(Dock *dock,size_t allocPos = 0);

    Dock *getHost() const {return host;}

private:
    void setHost(Dock *value) {host = value;}

private:
    Dock *host;
    StreamList *exportStream;
};

}

#endif // LINKER_H
