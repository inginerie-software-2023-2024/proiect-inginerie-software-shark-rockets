# Context
These days, there is a greater need than ever for computation and storage. In many cases, a single machine cannot manage datasets that are too big.
<br>
<br>
When this occurs, the work must be distributed, and distribution brings with it a host of issues that impede development work: synchronization between a cluster of machines, network latency, and data sharing.
<br>
<br>
When it comes to the actual work that needs to be done, implementing reliable communication and synchronization is just overhead for organizations dealing with large datasets, as they typically have multiple use cases where they need parallelization. This means that time and resources could be better utilized accomplishing other tasks.


# Product Vision
Koala is a programming library and Eucalypt is a monitoring solution catered to developers who want to process large amounts of raw data through computations that have to be distributed across machines.
<br>
<br>
Our product allows the user to express such computations in a straightforward manner while hiding the messy details of parallelization, data distribution and fault tolerance through a simple abstraction called the Map-Reduce programming model.
<br>
<br>
Its primary goal is to ease the development experience and outsource the responsability for handling common faults in distributed systems.
