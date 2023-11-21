import { Link } from "react-router-dom";
// @mui material components
import Grid from "@mui/material/Grid";
import Card from "@mui/material/Card";

// Material Dashboard 2 React components
import MDBox from "components/MDBox";
import MDTypography from "components/MDTypography";
import MDAlert from "components/MDAlert";

// Material Dashboard 2 React example components
import DashboardLayout from "examples/LayoutContainers/DashboardLayout";
import DashboardNavbar from "examples/Navbars/DashboardNavbar";
import Footer from "examples/Footer";
import DataTable from "examples/Tables/DataTable";

// Data
import authorsTableData from "layouts/user-management/data";
import { useEffect, useState } from "react";
import UserManagementService from "services/user-management-service";

const UserManagement = () => {
  const { columns, rows } = authorsTableData();

  const handleEdit = async (id, data) => {
    try {
      const response = await UserManagementService.editUser(id, data);
      console.log(response);
    }
    catch (error) {
      console.log(error);
    }
  }

  const handleDelete = async (id) => {
    try {
      const response = await UserManagementService.deleteUser(id);
      console.log(response);
    }
    catch (error) {
      console.log(error);
    }
  }

  const Action = ({ id }) => (
    <MDBox display="flex" justifyContent="center">
      <MDBox mr={1}>
        <MDTypography
          variant="button"
          fontWeight="bold"
          textColor="info"
          onClick={() => handleEdit(id)}
        >
          Edit
        </MDTypography>
      </MDBox>
      <MDBox ml={1}>
        <MDTypography
          variant="button"
          fontWeight="bold"
          textColor="error"
          onClick={() => handleDelete(id)}
        >
          Delete
        </MDTypography>

      </MDBox>
    </MDBox>
  );

  


  return (
    <DashboardLayout>
      <DashboardNavbar />
      <MDBox pt={6} pb={3}>
        <Grid container spacing={6}>
          <Grid item xs={12}>
            <Card>
              <MDBox
                mx={2}
                mt={-3}
                py={3}
                px={2}
                variant="gradient"
                bgColor="info"
                borderRadius="lg"
                coloredShadow="info"
              >
                <MDTypography variant="h6" color="white">
                  Users Table
                </MDTypography>
              </MDBox>
              <MDBox pt={3}>
                <DataTable
                  table={{ columns, rows }}
                  isSorted={false}
                  entriesPerPage={false}
                  showTotalEntries={false}
                  noEndBorder
                />
              </MDBox>
            </Card>
          </Grid>
        </Grid>
      </MDBox>
      <Footer />
    </DashboardLayout>
  );
};

export default UserManagement;
