# Product features and functionalities

Here, we have compiled the list of features and functionalities that deliver value to the stakeholders. Firstly, we will list them and give a brief description to align them with our product vision, and then we will lay out a product roadmap to show the important stages in the development and release process.

## List of features and functionalities

| **Feature**                 | **Description**                                                                                                                                                                                                                                                                              |
|-----------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Standard Kubernetes Setup | A sys-admin should bring the whole infrastructure up with minimal difficulties. As Kubernetes is an omnipresent choice for container orchestration in cloud, we will cater to this platform.                                                                                                              |
| Map-Reduce Library          | This product will provide the clients with a library with map-reduce semantics. As a lot of real-world problems can be reduced to the map-reduce programming model, we will cater to these semantics. This enable direct and concise expression of ideas in terms of functional computation. <br> Clients should implement the business logic, then link against the Koala library and enjoy the benefits of parallelization. |
| Parallel Task Execution     | The core feature of the product is the ability to leverage the functional map-reduce semantics in order to parallelize large computations. This leads to decreased execution time and empowers users to process data sets that would not fit in the memory of commodity hardware. <br> The coordination of the parallel tasks should not concern the user - this is abstracted in the Koala library that we provide.           |
| Resource Monitoring         | The product exposes a web-based resource monitor that can be used by admins to monitor resource usage and estimate costs. The use of resources can be examined over a longer period of time as well as in minute detail.                                                                     |
| User management             | Admins can onboard new users to the infrastructure and allow them to utilize the cluster of machines for their own computations. <br> Admins can also revoke accounts - in other words, users might be disallowed access to the resources of the cluster. <br> If a user does not have an account, he/she can still run map-reduce jobs, but on the local machine, with the benefits of concurrency but without the benefits of pure parallelism.                                                                                                                                                           |
| Cronjob setup               | Periodic (parallel) jobs can be set up to run on this infrastructure. This way, expensive periodic parallel computations get a simple, UNIX cron-like interface.                                                                                                                             |
| Quota adjustments           | Admins can set up limits for resource utilization, on a per-user basis. These quota limits can be adjusted to accommodate higher loads or to cut costs.   


## Product roadmap

|                                 | Sprint 1                                                                               | Sprint 2                                                          | Sprint 3                                                                       | Sprint 4                                                                                                                  |
|---------------------------------|----------------------------------------------------------------------------------------|-------------------------------------------------------------------|--------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------------------|
| Koala (Map-Reduce) library      | Guest: View sample jobs <br><br> Guest: Request account creation <br><br> Guest: Run a job locally | User: Run a job on the cluster <br><br> User: Configure I/O parameters | User: Configure recurring jobs                                               |                                                                                                                           |
| Eucalypt monitoring web service | Admin: Ban/delete users                                                              | Admin: Create accounts <br><br> Admin: Promote users                   | User: Monitor own ongoing jobs <br><br> Admin: Monitor all jobs, set usage quotas |                                                                                                                           |
| Kubernetes setup                |                                                                                        |                                                                   |                                                                                | Network admin: Set up infrastructure to run on Kubernetes <br><br> Network admin: Scale the cluster by adding/removing workers |

We aim to distribute the work as evenly as possible over the 4 sprints. We will mark the difficulty of user stories by (Fibonacci-sequence generated) story points.

Sprint 1 (6️⃣ story points):
- As a guest, I want to create a map-reduce job and run it concurrently on the local machine, without creating an account, so that I can try this product's functionalities (3️⃣ SP)
- As a guest, I want to submit a user account creation request so that I can benefit from the cluster's resources in the future (1️⃣ SP)
- As a guest, I want to view sample map-reduce jobs so that I can understand the capabilities of Koala (1️⃣ SP)
- As an admin, I want to delete/ban users so that I can manage the user base effectively (1️⃣ SP)

Sprint 2 (6️⃣ story points):
- As a user, I want to create a map-reduce job and submit it for computation on the cluster so that I can efficiently process large amounts of data (3️⃣ SP)
- As a user, I want to configure I/O parameters for map-reduce jobs, namely the number of input and output files, so that I have control over the size of the generated files (1️⃣ SP)
- As an admin, I want to accept user account creation requests so that new users can access the resources of the cluster (1️⃣ SP)
- As an admin, I want to be able to promote a user to admin status so that I can delegate administrative responsibilities (1️⃣ SP)

Sprint 3 (5️⃣ story points):
- As a user, I want to set up recurring or scheduled map-reduce jobs so that they can execute without manual triggering (3️⃣ SP)
- As a user, I want to monitor ongoing jobs created by me so that I can track their progress and view the statistics (1️⃣ SP)
- As an admin, I want to monitor all ongoing jobs and utilization metrics so that I can assess the performance and cost of the cluster (1️⃣ SP)

Sprint 4 (6️⃣ story points):
- As a network administrator, I want to be able to set up this infrastructure on my Kubernetes cluster, so that my organization can benefit from the parallelization features provided (3️⃣ SP)
- As a network administrator, I want to be able to scale the cluster by adding or removing machines dynamically so that the cluster perfectly fits the users’ needs (3️⃣ SP)
