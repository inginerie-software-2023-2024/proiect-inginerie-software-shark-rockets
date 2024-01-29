# Sprint report #4

### Dates of the sprint
10.01.2024 - 28.01.2024
<br>
Last commit hash: [da13ffa1d1fbcd3a7215c2b196b259a80c5b7c9e](https://github.com/inginerie-software-2023-2024/proiect-inginerie-software-shark-rockets/commit/da13ffa1d1fbcd3a7215c2b196b259a80c5b7c9e)
<br>
Recording of the sprint review: [YouTube](https://youtu.be/BunA39FKX0U)

### Overview of the team and their planned capacity
Full team available

### List of backlog items planned to be developed in the current sprint

<ul>
    <li>Addressed user stories (global list of user stories, along with acceptance criteria: [User stories](user_stories.md))
        <ul>
            <li>As a network administrator, I want to be able to set up this infrastructure on my Kubernetes cluster, so that my organization can benefit from the parallelization features provided</li>
            <li>As a network administrator, I want to be able to scale the cluster by adding or removing machines dynamically so that the cluster perfectly fits the users’ needs</li>
            <li>As a user, I want to set up recurring or scheduled map-reduce jobs so that they can execute without manual triggering</li>
        </ul>
    </li>
    <li>Items added after after the sprint start:
    <ul>
    <li><a href="https://github.com/inginerie-software-2023-2024/proiect-inginerie-software-shark-rockets/commit/f63cb0e1bc38958e3057359b837919284d7ecbbd">Redesign token generation page</a></li>
    <li><a href="https://github.com/inginerie-software-2023-2024/proiect-inginerie-software-shark-rockets/commit/da13ffa1d1fbcd3a7215c2b196b259a80c5b7c9e">End-to-end Koala testing</a></li>
    </ul>
    </li>
    <li>Items removed before the sprint end:
    <ul>
    <li>As a guest, I want to create a map-reduce job and run it *concurrently on the local machine*, without creating an account, so that I can try this product's functionalities</li>
    </ul>
    </li>
</ul>

### Status of planned items and their status
<ul>
<li>As a network administrator, I want to be able to set up this infrastructure on my Kubernetes cluster, so that my organization can benefit from the parallelization features provided
<ul>
<li>This item has been completed thoroughly</li>
<li>Helm is utilized to handle Kubernetes configuration files, simplifying the process of deploying infrastructures: With a single command, the core Koala library can be raised, and a separate command is used for the Eucalypt React app (Frontend).</li>
</ul>
</li>
<li>As a network administrator, I want to be able to scale the cluster by adding or removing machines dynamically so that the cluster perfectly fits the users’ needs
<ul>
<li>This item has been completed thoroughly</li>
<li>The number of worker pods is configurable through a parameter in the Helm chart: adding or removing pods can be accomplished with a single command. This seamless process is also attributed to prior efforts ensuring that workers register upon startup and inactive workers are purged through the use of heartbeats.</li>
</ul>
</li>
</li>
<li>As a user, I want to set up recurring or scheduled map-reduce jobs so that they can execute without manual triggering.
<ul>
<li>This item has been completed thoroughly</li>
<li>The period of time between subsequent runs of periodic jobs is now a CLI argument. Owners of periodic jobs can also easily kill them using the Eucalypt frontend</li>
</ul>
</li>
<li>As a guest, I want to create a map-reduce job and run it *concurrently on the local machine*, without creating an account, so that I can try this product's functionalities
<ul>
<li>This item has been abandoned</li>
<li>Because of time constraints, we deemed this task to have the lowest priority in both this sprint and the overall project; given that the project primarily emphasizes parallel processing rather than concurrent processing, we can easily incorporate this feature at a later date, as our existing library-master-worker infrastructure readily supports it.</li>
</ul>
</li>
</ul>

### Sprint review

During a challenging period marked by high contention among team members due to other projects and exam study time, our final sprint stands out as a success. We not only successfully incorporated the last remaining valuable functionality, enabling the scheduling of periodic jobs, but also deployed our infrastructure on Digital Ocean using Helm charts. Helm charts require little deployment effort, not only for us, but also for any potential client.

A noteworthy accomplishment of this sprint is the end-to-end testing of the Koala infrastructure, serving as a valuable complement to the existing unit testing for the library. Given the interconnected nature of our project's various communicating processes, treating the system as a whole through end-to-end testing became particularly relevant.

The only setback could be perceived as the inability to implement the last user story, which focused on allowing guests to create and run map-reduce jobs concurrently on the local machine without creating an account. However, this feature, while not crucial to the product's core ethos of parallel programming, can be easily integrated at a later date, as our current library-master-worker infrastructure readily supports it.

Concluding this ambitious project, which involved the utilization of C++, JavaScript with Node.js & React, Python, bash scripting, and various CI tools, we take pride in the achieved work. We successfully completed 12 out of 13 user stories, improved several initially proposed implementations, and subjected the application to rigorous unit testing, end-to-end testing, and manual testing. Team coordination remained exemplary, allowing us to navigate each sprint with flexibility, adjusting priorities within the current sprint while seamlessly pushing others to subsequent sprints. This was achieved while implementing all core functionalities of the product and incorporating the majority of the nice touches.