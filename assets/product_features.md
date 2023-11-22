# Product features and functionalities

Here, we have compiled the list of features and functionalities that deliver value to the stakeholders. Firstly, we will list them and give a brief description to align them with our product vision, and then we will lay out a product roadmap to show the important stages in the development and release process.

## List of features and functionalities

| **Feature**                 | **Description**                                                                                                                                                                                                                                                                              |
|-----------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Effortless Kubernetes Setup | A sys-admin should bring the whole infrastructure up with only one command. As Kubernetes is an omnipresent choice for container orchestration, we will cater to this platform.                                                                                                              |
| Map-Reduce Library          | This product will provide the clients with a library with map-reduce semantics. As a lot of real-world problems can be reduced to the map-reduce programming model, we will cater to these semantics. This enable direct and concise expression of ideas in terms of functional computation. |
| Parallel Task Execution     | The core feature of the product is the ability to leverage the functional map-reduce semantics in order to parallelize large computations. This leads to decreased execution time and empowers users to process data sets that would not fit in the memory of commodity hardware.            |
| Resource Monitoring         | The product exposes a web-based resource monitor that can be used by admins to monitor resource usage and estimate costs. The use of resources can be examined over a longer period of time as well as in minute detail.                                                                     |
| User onboarding             | Admins can onboard new users to the infrastructure and allow them to utilize the cluster of machines for their own computations.                                                                                                                                                             |
| Cronjob setup               | Periodic (parallel) jobs can be set up to run on this infrastructure. This way, expensive periodic parallel computations get a simple, UNIX cron-like interface.                                                                                                                             |
| Quota adjustments           | Admins can set up limits for resource utilization, on a per-user basis. These quota limits can be adjusted to accommodate higher loads.   


## Product roadmap

![Roadmap](Roadmap.png)

We aim to distribute the work as evenly as possible over the 4 sprints. We will mark the difficulty of user stories by (Fibonacci-sequence generated) story points.

Sprint 1 (6️⃣ story points):
- As a guest, I want to create a map-reduce job and submit it on the local machine so that I can explore the functionality of the product without creating an account (3️⃣ SP)
- As a guest, I want to submit a user account creation request so that I can access additional features and save my jobs for future reference (1️⃣ SP)
- As a guest, I want to view sample map-reduce jobs so that I can understand the capabilities of Koala (1️⃣ SP)
- As a network administrator, I want to configure the cluster so that I can optimize its performance and ensure proper functionality (1️⃣ SP)

Sprint 2 (6️⃣ story points):
- As a user, I want to create a map-reduce job and submit it for computation on the cluster so that I can efficiently process large amounts of data (3️⃣ SP)
- As a user, I want to configure custom parameters for a map-reduce job, such as input/output locations and computation settings so that the job fits my needs (3️⃣ SP)
- As a user, I want to monitor ongoing jobs created by me so that I can track their progress and view the statistics (1️⃣ SP)
- As an admin, I want to monitor all ongoing jobs and utilization metrics so that I can assess the performance and efficiency of the cluster (1️⃣ SP)

Sprint 3 (6️⃣ story points):
- As a user, I want to set up recurring or scheduled map-reduce jobs so that I can set up jobs for when I'm not at my PC (3️⃣ SP)
- As an admin, I want to accept user account creation requests so that new users can access the full functionality of the product (1️⃣ SP)
- As an admin, I would like to delete user accounts so that I can manage the user base effectively (1️⃣ SP)
- As an admin, I want to be able to promote a user to admin status so that I can delegate administrative responsibilities (1️⃣ SP)

Sprint 4 (5️⃣ story points):
- As a network administrator, I want to be able to scale the cluster by adding or removing machines dynamically so that the cluster perfectly fits the users’ needs (5️⃣ SP)
