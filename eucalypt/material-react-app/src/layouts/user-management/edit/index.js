import React, { useEffect, useState } from 'react';
import { useParams, useNavigate } from 'react-router-dom';
import UserManagementService from 'services/user-management-service';

// @mui material components
import Grid from "@mui/material/Grid";
import Card from "@mui/material/Card";
import TextField from "@mui/material/TextField";
import Button from "@mui/material/Button";

// Material Dashboard 2 React components
import MDBox from "components/MDBox";
import MDTypography from "components/MDTypography";
import MDAlert from "components/MDAlert";
import MDButton from "components/MDButton";
import NumberInput from 'examples/NumberInput';

// Material Dashboard 2 React example components
import DashboardLayout from "examples/LayoutContainers/DashboardLayout";
import DashboardNavbar from "examples/Navbars/DashboardNavbar";
import Footer from "examples/Footer";
import MenuItem from "@mui/material/MenuItem";
import Select from "@mui/material/Select";


const EditUser = () => {
    const { id } = useParams();
    const navigate = useNavigate();
    const [user, setUser] = useState(null);

    useEffect(() => {
        const fetchUser = async () => {
            try {
                const response = await UserManagementService.getUser(id);
                setUser(response.data);
            } catch (err) {
                console.error(err);
            }
        };
        fetchUser();
    }, [id]);

    const handleInputChange = (event) => {
        const { name, value } = event.target;
        setUser({ ...user, [name]: value });
    };

    const handleSubmit = async (event) => {
        event.preventDefault();
        try {
            await UserManagementService.editUser(id, user);
            console.log('User updated successfully!');
            navigate('/user-management');
        } catch (err) {
            console.error(err);
        }
    };

    if (!user) return 'Loading...';

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
                                <form onSubmit={handleSubmit}>
                                    <TextField
                                        name="name"
                                        label="Name"
                                        value={user.name}
                                        onChange={handleInputChange}
                                        fullWidth
                                        margin="normal"
                                    />
                                    <TextField
                                        name="email"
                                        label="Email"
                                        value={user.email}
                                        onChange={handleInputChange}
                                        fullWidth
                                        margin="normal"
                                    />

                                    <TextField
                                        name="role"
                                        label="Role"
                                        fullWidth
                                        margin="normal"
                                        select
                                        value={user.role}
                                        onChange={handleInputChange}
                                    >
                                        <MenuItem value="pending_approval">Pending approval</MenuItem>
                                        <MenuItem value="user">Registered user</MenuItem>
                                        <MenuItem value="admin">Admin</MenuItem>
                                    </TextField>

                                    <TextField
                                        name="quota"
                                        label="Quota"
                                        fullWidth
                                        margin="normal"
                                        value={user.quota}
                                        onChange={handleInputChange}
                                    >                                        
                                        <NumberInput>
                                        </NumberInput>
                                    </TextField>

                                    <MDButton
                                        variant="contained"
                                        color="info"
                                        fullWidth
                                        type="submit"
                                    >
                                        Save
                                    </MDButton>
                                </form>
                            </MDBox>
                        </Card>
                    </Grid>
                </Grid>
            </MDBox>
            <Footer />
        </DashboardLayout>
    );
};

export default EditUser;