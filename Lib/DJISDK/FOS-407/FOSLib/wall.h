/*! @abstract
 * */

#ifndef WALL_H
#define WALL_H
#include <stdint.h>
/*! @note Wall Modle description
 *
 *
 *
 * */
typedef struct
{
    int64_t start;
    int64_t end;
    int64_t height;
    int64_t basement;
    double alpha;
}WallModle;
class Wall
{
public:
    Wall();
private:

};

#endif // WALL_H
