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
// import Accordion from "@mui/material/Accordion";
import MDAccordion from "components/MDAccordion";
import ArrowDownwardIcon from '@mui/icons-material/ArrowDownward';
import MDTypography from "components/MDTypography";


function Dashboard() {
    const { processedUserData, dateOfFetch } = jobData();
    return (
        <DashboardLayout>
            <DashboardNavbar />
            <MDBox mt={5}>
                {processedUserData.map((data, index) => (
                    <MDAccordion key={index} mb={10} sx={{ border: '1px solid black', borderRadius: '8px' }}>
                        <MDAccordion.Summary
                            expandIcon={<ArrowDownwardIcon />}
                            aria-controls="panel1-content"
                            id="panel1-header"
                        >
                            <MDTypography color="text" fontWeight="light">
                                {data.user.name}
                            </MDTypography>
                        </MDAccordion.Summary>
                        <MDAccordion.Details sx={{ display: 'flex', flexDirection: 'column', alignItems: 'center' }}>
                            <MDBox mt={10} sx={{ width: '80%' }}>
                                {data.jobUtilizationData.length != 0 ? (
                                    <Grid container spacing={1}>
                                        {data.jobUtilizationData.map((job, jobIndex) => (
                                            <Grid item key={jobIndex} xs={12} md={12} lg={12}>
                                                <MDBox mb={10}>
                                                    <ReportsBarChart
                                                        color="dark"
                                                        title={`Job ${jobIndex + 1} Utilization`}
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
                                ) : (
                                    <MDTypography color="text" fontWeight="light">
                                        {"No job details available for this user."}
                                    </MDTypography>
                                )}
                            </MDBox>
                        </MDAccordion.Details>
                    </MDAccordion>
                ))}
            </MDBox>
        </DashboardLayout>
    );
}


export default Dashboard;
