#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <stdint.h>
/*! @module  Level logical
 *  @author  Wu Hao
 *  @date    2015-08-17
 * */
namespace Logic
{
enum Plan
{
    PlanA = 0,
    PlanB = 1,
    PlanC = 2,
    TestTakeOff = 3,
    TestTurn = 4,
    //!@todo add more test
};
}
void init();
void start(Logic::Plan Plan);
void autoTestAll();
void emergency();
void printState();

/*! @module  Level flight control
 *  @author  William Wu
 *  @date    2015-08-17
 * */

/*! @chapter interface for Logical Level
 * */
bool takeOff(void);
bool turnTo(float angle);
bool moveTo(float x,float y,float z);
bool trackSquare(int number);
bool trackBasket();
bool trackCircle();
bool throwBall();
bool land();
bool takeBall();
/*! @endchapter*/

void init();
void start();
void freePoll();
#endif // STATEMACHINE_H
