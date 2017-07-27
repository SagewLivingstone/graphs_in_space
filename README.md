# Graphs in Space (final project)

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


**Running**

  A precompiled windows binary is provided under /VectorSpace/x64/VectorSpace in case compiling does not
work.
