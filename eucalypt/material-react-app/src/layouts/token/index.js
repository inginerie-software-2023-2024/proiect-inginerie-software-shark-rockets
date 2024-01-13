import DashboardLayout from "examples/LayoutContainers/DashboardLayout";
import DashboardNavbar from "examples/Navbars/DashboardNavbar";
import Footer from "examples/Footer";
import Card from "@mui/material/Card";

import { useContext, useState, useEffect } from "react";
import { AuthContext } from "context";
import connectionService from "services/connection-service";

import MDBox from "components/MDBox";
import MDButton from "components/MDButton";
import { Grid } from "@mui/material";
import MDTypography from "components/MDTypography";



function Token() {
    const authContext = useContext(AuthContext);
    let [expirationDate, setExpirationDate] = useState("Generate a new token");
    let [token, setToken] = useState("Your Token");

    useEffect(() => {
        async function fetchData() {
            console.log(authContext.id);
            const response = await connectionService.getToken(authContext.id);
            console.log(response, response.id || token);
            setToken(response.id || token)
            setExpirationDate(response.expiration_date || "Generate a token to see an expiration date");
            console.log(token);
        }
        
        fetchData();
    }, []);

    const generateToken = async () => {
        const response = await connectionService.generateToken(authContext.id);
        console.log(response.id, response.id || token);
        setToken(response.id || token)
        setExpirationDate(response.expiration_date || "Generate a token to see an expiration date");
        console.log(token);
    }

    return (<DashboardLayout>
        <DashboardNavbar />
        <MDBox mb = {6} mt = {3}>
            <Grid container spacing={6} justifyContent="center">
                <Grid item xs={12} >
                    <Card>
                        <MDBox>
                            <MDButton
                            variant="gradient"
                            color="info"
                            type="button"
                            onClick={generateToken}
                            >
                                Generate Token
                            </MDButton>
                        </MDBox>

                        <MDBox>
                            <MDTypography
                            variant="gradient"
                            color="info"
                            type="button"                                     
                            >
                                {token} will expire on {expirationDate}
                            </MDTypography>
                        </MDBox>
                    </Card>
                </Grid>
            </Grid>
        </MDBox>

    </DashboardLayout>);
}

export default Token;
