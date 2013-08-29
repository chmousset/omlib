omlib
=====

Open Motion library. Motion path &amp; planning


This lib contains the essential parts of a real-time motion planner.
It uses cubic splines to represent a path to follow, and has a planner to feed the motion controller in real-time

Spline operation:
 - lenght lookup table computation
 - point coordinate calculation
 - tangeant (speed) calculation
 - acceleration calculation
 - splitting of a spline in half
 - max speed / acceleration check
 - path complexity evaluation
 
Planner Operation
 - FIFO buffer
 - dynamic or fixed size buffer
 - dynamic job type &amp; data size
 - mutexless thread-safe for smooth real-time operation

Configuration
 - single-axis (embedded controller) or multi-axis
 - fixed size buffer (embedded) or dynamic size buffer