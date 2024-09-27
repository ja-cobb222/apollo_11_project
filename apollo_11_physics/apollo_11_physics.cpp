/*************************************************************
 * 1. Name:
 *      -your name-
 * 2. Assignment Name:
 *      Practice 02: Physics simulator
 * 3. Assignment Description:
 *      Compute how the Apollo lander will move across the screen
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, etc.
 **************************************************************/

#include <iostream>  // for CIN and COUT
#include <cmath>    // for sin, cos, sqrt
using namespace std;

#define WEIGHT   15103.000   // Weight in KG
#define GRAVITY     -1.625   // Vertical acceleration due to gravity, in m/s^2
#define THRUST   45000.000   // Thrust of main engine, in Newtons (kg m/s^2)


/***************************************************
 * COMPUTE DISTANCE
 * Apply inertia to compute a new position using the distance equation.
 * The equation is:
 *     s = s + v t + 1/2 a t^2
 * INPUT
 *     s : original position, in meters
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     s : new position, in meters
 **************************************************/

double computeDistance(double s, double v, double a, double t)
{
    return s + v * t + 0.5 * a * t * t;
}


/**************************************************
 * COMPUTE ACCELERATION
 * Find the acceleration given a thrust and mass.
 * This will be done using Newton's second law of motion:
 *     f = m * a
 * INPUT
 *     f : force, in Newtons (kg * m / s^2)
 *     m : mass, in kilograms
 * OUTPUT
 *     a : acceleration, in meters/second^2
 ***************************************************/

double computeAcceleration(double f, double m)
{
   return f / m;
}


/***********************************************
 * COMPUTE VELOCITY
 * Starting with a given velocity, find the new
 * velocity once acceleration is applied. This is
 * called the Kinematics equation. The
 * equation is:
 *     v = v + a t
 * INPUT
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     v : new velocity, in meters/second
 ***********************************************/

double computeVelocity(double v, double a, double t)
{
   return v + a * t;
}


/***********************************************
 * COMPUTE VERTICAL COMPONENT
 * Find the vertical component of a velocity or acceleration.
 * The equation is:
 *     cos(a) = y / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     y : the vertical component of the total
 ***********************************************/

double computeVerticalComponent(double a, double total)
{
   return cos(a) * total;
}


/***********************************************
 * COMPUTE HORIZONTAL COMPONENT
 * Find the horizontal component of a velocity or acceleration.
 * The equation is:
 *     sin(a) = x / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     x : the vertical component of the total
 ***********************************************/

double computeHorizontalComponent(double a, double total)
{
   return sin(a) * total;
}


/************************************************
 * COMPUTE TOTAL COMPONENT
 * Given the horizontal and vertical components of
 * something (velocity or acceleration), determine
 * the total component. To do this, use the Pythagorean Theorem:
 *    x^2 + y^2 = t^2
 * where:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    | /
 *    |/
 * INPUT
 *    x : horizontal component
 *    y : vertical component
 * OUTPUT
 *    total : total component
 ***********************************************/

double computeTotalComponent(double x, double y)
{
   return sqrt(x * x + y * y);
}


/*************************************************
 * RADIANS FROM DEGEES
 * Convert degrees to radians:
 *     radians / 2pi = degrees / 360
 * INPUT
 *     d : degrees from 0 to 360
 * OUTPUT
 *     r : radians from 0 to 2pi
 **************************************************/

double radiansFromDegrees(double d)
{
   return d * acos(-1.0) / 180.0;
}


/**************************************************
 * PROMPT
 * A generic function to prompt the user for a double
 * INPUT
 *      message : the message to display to the user
 * OUTPUT
 *      response : the user's response
 ***************************************************/

double prompt(const char* message)
{
   double response;
   cout << message;
   cin >> response;
   return response;
}


void simulate(double& x, double& y, double& dx, double& dy, double angle, double time, int duration) {
   double mass = WEIGHT;
   double thrustAccel = THRUST / mass;
   double aRadians = radiansFromDegrees(angle);

   for (int t = 1; t <= duration; t++) {
      // Compute acceleration components
      double ddxThrust = thrustAccel * sin(aRadians);  // Horizontal acceleration due to thrust
      double ddyThrust = thrustAccel * cos(aRadians);  // Vertical acceleration due to thrust
      double ddx = ddxThrust;   // Total horizontal acceleration
      double ddy = ddyThrust + GRAVITY;   // Total vertical acceleration

      // Update position before updating velocity
      x = x + dx * time + 0.5 * ddx * time * time;
      y = y + dy * time + 0.5 * ddy * time * time;

      // Update velocity
      dx = dx + ddx * time;
      dy = dy + ddy * time;

      // Calculate total velocity (speed)
      double speed = sqrt(dx * dx + dy * dy);

      // Display results
      cout.setf(ios::fixed | ios::showpoint);
      cout.precision(2);
      cout << t << "s - x,y:(" << x << ", " << y << ")m  ";
      cout << "dx,dy:(" << dx << ", " << dy << ")m/s  ";
      cout << "speed:" << speed << "m/s  ";
      cout << "angle:" << angle << "deg\n";
   }
}

int main() {
   // Initial inputs
   double dx = prompt("What is your horizontal velocity (m/s)? ");
   double dy = prompt("What is your vertical velocity (m/s)? ");
   double y = prompt("What is your altitude (m)? ");
   double x = 0;  // Initial horizontal position is zero
   double angle = prompt("What is the angle of the LM where 0 is up (degrees)? ");
   double time = 1;  // Time interval is 1 second

   // Simulate for 5 seconds
   simulate(x, y, dx, dy, angle, time, 5);

   // Allow the user to update the angle
   angle = prompt("What is the new angle of the LM where 0 is up (degrees)? ");

   // Simulate for another 5 seconds
   simulate(x, y, dx, dy, angle, time, 5);

   return 0;
}