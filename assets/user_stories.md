# Koala - User stories

## Guest (cannot access cluster resources, as he/she does not have an account created by the administrator)
- As a guest, I want to create a map-reduce job and run it *concurrently on the local machine*, without creating an account, so that I can try this product's functionalities.
    - Scenario: Creation of a new map-reduce job on the local machine.
        - Given: The guest has compiled a new map-reduce computation.  
        - And: Has created a local cluster.
        - When: The guest runs it. 
        - Then: The job is scheduled and executed on the local cluster. 

- As a guest, I want to submit a user account creation request so that I can benefit from the cluster's resources in the future.
    - Scenario: Successful creation of a new account. 
        - Given: The guest is on the registration page.
        - When: The guest enters valid details.
        - And: Submits the registration form.
        - Then: A new user is created.

    - Scenario: Registration with invalid details. 
        - Given: The guest is on the registration page.
        - When: The guest enters invalid details.
        - And: Submits the registration form.
        - Then: The user should see error messages for the invalid fields.

- As a guest, I want to view sample map-reduce jobs so that I can understand the capabilities of Koala.
    - Scenario: Viewing sample map-reduce jobs.
        - Given: The guest is on the sample page.
        - When: The user clicks on a sample job.
        - Then: The sample source is downloaded on guest's machine.

## User (can access cluster resources, as he/she has an account created by the administrator)
- As a user, I want to create a map-reduce job and submit it for computation *on the cluster* so that I can efficiently process large amounts of data.
- As a user, I want to configure I/O parameters for map-reduce jobs, namely the number of input and output files, so that I have control over the size of the generated files.
- As a user, I want to monitor ongoing jobs created by me so that I can track their progress and view utilization statistics.
- As a user, I want to set up recurring or scheduled map-reduce jobs so that they can execute without manual triggering.

## Admin
- As an admin, I want to delete/ban users so that I can manage the user base effectively.
    - Scenario: Banning an user.
        - Given: The administrator is on the user page.
        - When: The administrator clicks on the ban user button.
        - Then: The user is banned and a message is displayed to the administrator.
- As an admin, I want to accept user account creation requests so that new users can access the resources of the cluster.
- As an admin, I want to monitor all ongoing jobs and utilization metrics so that I can assess the performance and cost of the cluster.
- As an admin, I want to be able to promote a user to admin status so that I can delegate administrative responsibilities.

## Network Administrator
- As a network administrator, I want to be able to set up this infrastructure on my Kubernetes cluster, so that my organization can benefit from the parallelization features provided.
- As a network administrator, I want to be able to scale the cluster by adding or removing machines dynamically so that the cluster perfectly fits the users’ needs.
