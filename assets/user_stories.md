# Koala - User stories

## Guest (cannot access cluster resources, as he/she does not have an account created by the administrator)
- As a guest, I want to create a map-reduce job and run it *concurrently on the local machine*, without creating an account, so that I can try this product's functionalities.
    - Scenario: Creation of a new map-reduce job on the local machine
        - Given: The guest has compiled a new map-reduce computation. 
        - And: Has created a local cluster
        - When: The guest runs it
        - Then: The job is scheduled and executed on the local cluster

- As a guest, I want to submit a user account creation request so that I can benefit from the cluster's resources in the future.
    - Scenario: Successful creation of a new account
        - Given: The guest is on the registration page
        - When: The guest enters valid details
        - And: Submits the registration form
        - Then: A new user is created

    - Scenario: Registration with invalid details
        - Given: The guest is on the registration page
        - When: The guest enters invalid details
        - And: Submits the registration form
        - Then: The user should see error messages for the invalid fields

- As a guest, I want to view sample map-reduce jobs so that I can understand the capabilities of Koala.
    - Scenario: Viewing sample map-reduce jobs
        - Given: The guest is on the sample page
        - When: The user clicks on a sample job
        - Then: The sample source is downloaded on guest's machine

## User (can access cluster resources, as he/she has an account created by the administrator)
- As a user, I want to create a map-reduce job and submit it for computation *on the cluster* so that I can efficiently process large amounts of data.
    - Scenario: User submits a map-reduce job
        - Given: The user has a valid account
        - When: The user fsends a job request
        - Then: The user should receive a confirmation message and be able to track the job status

- As a user, I want to configure I/O parameters for map-reduce jobs, namely the number of input and output files, so that I have control over the size of the generated files.
    - Scenario: A user wants to start a new map reduce job with custom input and output files
        - Given: The user has developed their algorithm
        - When: The user specifies a glob pattern to match their input files and provides the number R for the desired output files
        - Then: he job starts using the provided files as input and generates output distributed across R files

- As a user, I want to monitor ongoing jobs created by me so that I can track their progress and view utilization statistics.
    - Scenario: A user wants to monitor the progress of their job
        - Given: The user has already starated a job
        - When: The user navigates to the job graph page within Eucalypt
        - Then: The user is presented with visibility into both completed and ongoing map and reduce tasks associated with their job

- As a user, I want to set up recurring or scheduled map-reduce jobs so that they can execute without manual triggering.
    - Scenario: A user wants to set up a recurring job
        - Given: The user has developed their algorithm
        - When: The user starts the job, specifying a flag to determine the frequency of recurrence
        - Then: The job runs at regular intervals as defined by the specified frequency

## Admin
- As an admin, I want to delete/ban users so that I can manage the user base effectively.
    - Scenario: Banning an user
        - Given: The administrator is on the user page
        - When: The administrator clicks on the ban user button
        - Then: The user is banned and a message is displayed to the administrator

- As an admin, I want to accept user account creation requests so that new users can access the resources of the cluster.
    - Scenario: Admin reviews a user account creation request
        - Given: The admin is logged in and has pending account creation requests
        - When: The admin reviews a request
        - Then: A refused request should be deleted, an accepted request should grant the user login capabilities

- As an admin, I want to monitor all ongoing jobs and utilization metrics so that I can assess the performance and cost of the cluster.
    - Scenario: An admin wants to monitor any job across the cluster
        - Given: The admin navigates to the job graph page within Eucalypt
        - When:  The admin selects a specific job for analysis
        - Then: The admin is presented with visibility into both completed and ongoing map and reduce tasks associated with the chosen job

- As an admin, I want to be able to promote a user to admin status so that I can delegate administrative responsibilities.
    - Scenario: Admin promotes a user to admin status
        - Given: The admin is logged in and has access to user management
        - When: The admin promotes a user to admin status
        - Then: The user should receive admin capabilities

## Network Administrator
- As a network administrator, I want to be able to set up this infrastructure on my Kubernetes cluster, so that my organization can benefit from the parallelization features provided.
    - Scenario: The network administrator wants to deploy the Koala & Eucalypt product on the company's cluster
        - Given: The network administrator has the Helm chart that has the necessary K8s configuration
        - When: The network administrator configures the deployment settings to match their preferences and executes the Helm installation command
        - Then: The Koala & Eucalypt solution becomes operational on the company's cluster

- As a network administrator, I want to be able to scale the cluster by adding or removing machines dynamically so that the cluster perfectly fits the users’ needs.
    - Scenario: The network administrator wants to scale the infrastructure to contain costs or provide additional compute resources to developers
        - Given: The network administrator wants to either increase or decrease the count of worker pods
        - When: The network administrator configures the desired number of worker instances in the Helm configuration
        - Then: The cluster will have less or more worker pods, so as to match the network administrator's specifications
