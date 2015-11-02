#ifndef MMU_H
#define MMU_H
#include "FOSCore.h"
namespace FOS
{
typedef struct RecordStructure
{
    Record* pre;
    void*   host;
    size_t  size;
}RecordNode;

class Record
{

};

class MMU
{
public:
    MMU();
    void* push(size_t size);
    void  pop(size_t size);

    void* malloc(size_t size,bool asStatic = false);
    void free(void* pointer);

    void printUsage();
private:
    void* debris(size_t size);
    void recycle(void* pointer,size_t size);

private:
    /*! @note Garbage recycle.
     *  Once the size of a pice of memory is less than a Record's size.
     *  It will become a garbage memory,
     *  because to record this memory's usage status,
     *  would use more memory than itself.
     * */

    void* memory;
    size_t size;
    size_t inHeap;
    Record stack;
    Record garbage;
};

}

#endif // MMU_H
