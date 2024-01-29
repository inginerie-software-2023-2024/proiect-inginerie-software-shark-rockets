/**
 =========================================================
 * Material Dashboard 2 React - v2.1.0
 =========================================================

 * Product Page: https://www.creative-tim.com/product/material-dashboard-react
 * Copyright 2022 Creative Tim (https://www.creative-tim.com)

 Coded by www.creative-tim.com

 =========================================================

 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 */

// @mui material components
import Grid from "@mui/material/Grid";

// Material Dashboard 2 React components
import MDBox from "components/MDBox";

// Material Dashboard 2 React example components
import DashboardLayout from "examples/LayoutContainers/DashboardLayout";
import DashboardNavbar from "examples/Navbars/DashboardNavbar";
import ReportsBarChart from "examples/Charts/BarCharts/ReportsBarChart";

// Data
import jobData from "layouts/dashboard/data/jobData";


function Dashboard() {
    const { jobUtilizationData, dateOfFetch } = jobData();
    return (
        <DashboardLayout>
            <DashboardNavbar />
            <MDBox mt={10}>
                <Grid container spacing={1}>
                    {jobUtilizationData.map((job, index) => (
                        <Grid item key={index} xs={12} md={12} lg={12}>
                            <MDBox mb={10}>
                                <ReportsBarChart
                                    color="dark"
                                    title={`Job ${index + 1} Utilization`}
                                    description={`User: ${job.user}`}
                                    date={`Date of job: ${job.date ? job.date.toLocaleString() : 'N/A'}`}
                                    actualizationDate={`Last actualization: ${dateOfFetch ? dateOfFetch.toLocaleString() : 'N/A'}`}
                                    chart={{
                                        labels: job.tasks.map((task) => (task.type)).concat("job"),
                                        datasets: {
                                            data: job.tasks.map((task) => ([task.start_ms.toFixed(2), task.complete_ms.toFixed(2)])).concat([[job.start_ms.toFixed(2), job.complete_ms.toFixed(2)]]),
                                        },
                                    }}
                                    lineHeightsY={job.tasks.length + 1}
                                />
                            </MDBox>
                        </Grid>
                    ))}
                </Grid>
            </MDBox>
        </DashboardLayout>
    );
}

export default Dashboard;
