# Graphs in Space (final project)
### Sage Livingstone

**Purpose**

  This project is an experiment with visualizing graphs in 3D space. Every node can contain
any number of child nodes forming a tree. Child nodes will orbit the parent node and can collide
with each other. Clicking on a root node will break off a chunk of it to create a child node. When
child nodes collide, they will combine their sizes and momentum. If a node becomes too large, it
will break off from it's parent and create it's own system. Root nodes are organized in a graph and
have links (edges) that connect each other together. Each edge has a distance setting that will force
the nodes to be a certain distance away from each other. If two root nodes come too close to each other,
they will form a link and separate (within a certain limit, because nodes have a maximum number of links).

**Building**

  First clone the master branch or download as a zip file. The source code is in \VectorSpace\VectorSpace

  To build and run a SFML program you must set up a proper project. A Visual Studio project is
already included in the project files but may need to be tweaked to work correctly (see specifics).
If using another IDE, you can set up the project as shown in https://www.sfml-dev.org/tutorials/2.4/.
(If your IDE is not listed, you can build with CMake). Essentially, you must add /SFML/include
to the additional include directories of your project, and add /SFML/lib to the library directives
for the linker. Also, ensure that sfml-graphics.lib, sfml-window.lib, and sfml-system.lib are
included in the project. Then build main.cpp and run. 

A precompiled windows binary is provided under /VectorSpace/x64/VectorSpace in case compiling does not 
work. Unfortunately, although SFML is cross-platform, it does not make project setup and compiling
easy. (It is meant to always distribute final versions as binaries)

**Running**

* Arrow Keys - Camera
* Scroll Wheel - Zoom In/Out
* Left Mouse Button - (On root node) Break off a piece of the selected node
* Right Mouse Button - (On root node) Finds largest node connected to selected node and breaks it off the chain
* Tilde (~) - Toggle Frame Counter

Other Notes:
* If window is too small/large, you can change the resolution in Space.h under WindowData. Make sure to rebuild project to ensure changes apply. (Note: SFML does not like windows that are larger than the screen resolution for Windows)
* Updates are tied to the framerate - if your framerate is not around 60-144 the simulation may be too fast/slow
* The bulk of Space.cpp handles taking 3D coordinates and converting them to 2D screen space
* I worked alone on this, the other account with commits is my desktop at home.

Open Issues/Bugs:
* Break off chain does not always delete all links
* It is very unlikely for child nodes to create their own children
* Objects too far away from camera will snap to center of screen and in extreme cases may be too large.
* Needs mouse movement (instead of arrow keys)
* Color of children of the first node will always be the same because the GetRandom() function uses runtime
* Currently no way to reset world other than closing program
