import DashboardLayout from "examples/LayoutContainers/DashboardLayout";
import DashboardNavbar from "examples/Navbars/DashboardNavbar";
import Footer from "examples/Footer";
import Card from "@mui/material/Card";
import Tooltip from "@mui/material/Tooltip";
import FileCopyIcon from "@mui/icons-material/FileCopy";
import IconButton from "@mui/material/IconButton";
import Divider from "@mui/material/Divider";
import Icon from "@mui/material/Icon";

import {useContext, useState, useEffect} from "react";
import {AuthContext} from "context";
import connectionService from "services/connection-service";

import MDBox from "components/MDBox";
import MDButton from "components/MDButton";
import {Grid} from "@mui/material";
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
    const copyToClipboard = (text) => {
        navigator.clipboard.writeText(text);
    };

    return (
        <DashboardLayout>
            <DashboardNavbar/>
            <MDBox mb={6} mt={3}>
                <Grid container spacing={6} justifyContent="center">
                    <Grid item xs={12}>
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
                        <Card sx={{height: "70%", marginTop: 4}}>
                            <MDBox pt={3} pb={1} px={1}>
                                <MDBox display="flex" alignItems="center">
                                    <MDTypography color="text" fontWeight="light">
                                        {token}
                                    </MDTypography>
                                    <IconButton onClick={() => copyToClipboard(token)}>
                                        <FileCopyIcon/>
                                    </IconButton>
                                </MDBox>
                                <Divider/>
                                <MDBox display="flex" alignItems="center">
                                    <MDTypography variant="button" color="text" lineHeight={1} sx={{mt: 0.15, mr: 0.5}}>
                                        <Icon>schedule</Icon>
                                    </MDTypography>
                                    <MDTypography variant="button" color="text" fontWeight="light">
                                        Expire at: {expirationDate != "Generate a token to see an expiration date" ? (
                                        new Date(expirationDate).toLocaleString()
                                    ) : (
                                        "Generate a token to see an expiration date"
                                    )}
                                    </MDTypography>
                                </MDBox>
                            </MDBox>
                        </Card>
                    </Grid>
                </Grid>
            </MDBox>
        </DashboardLayout>
    );
}

export default Token;
