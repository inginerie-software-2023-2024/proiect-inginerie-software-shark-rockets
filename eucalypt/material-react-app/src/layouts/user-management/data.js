/* eslint-disable react/prop-types */
/* eslint-disable react/function-component-definition */
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

// Material Dashboard 2 React components
import MDBox from "components/MDBox";
import MDTypography from "components/MDTypography";
import MDAvatar from "components/MDAvatar";
import MDBadge from "components/MDBadge";

// Images
import team2 from "assets/images/team-2.jpg";
import team3 from "assets/images/team-3.jpg";
import team4 from "assets/images/team-4.jpg";

import { getUsers } from "services/htttp.service";
import { useEffect, useState } from "react";

export default function data() {
  const [users, setUsers] = useState([]);

  useEffect(() => {
    const fetchUsers = async () => {
      try {
        const response = await getUsers();
        setUsers(response.data);
      } catch (err) {
        console.error(err);
      }
    };
    fetchUsers();
  }, []);

  console.log(users);

  const Author = ({ image, name, email }) => (
    <MDBox display="flex" alignItems="center" lineHeight={1}>
      <MDAvatar src={image} name={name} size="sm" />
      <MDBox ml={2} lineHeight={1}>
        <MDTypography display="block" variant="button" fontWeight="medium">
          {name}
        </MDTypography>
        <MDTypography variant="caption">{email}</MDTypography>
      </MDBox>
    </MDBox>
  );


  return {
    columns: [
      { Header: "user", accessor: "user", width: "45%", align: "left" },
      { Header: "email", accessor: "email", align: "left" },
      { Header: "creation date", accessor: "creationdate", align: "center" },
      { Header: "action", accessor: "action", align: "center" },
    ],

    rows: users.map((user) => ({
      user: <Author image={team2} name={user.name} email={user.email} />,
      email: user.email,
      creationdate: user.created_at,
      action: (
        <MDBox display="flex" justifyContent="center">
          <MDBadge color="success" variant="dot" anchorOrigin={{ vertical: "top", horizontal: "right" }} />
        </MDBox>
      ),
    })),
  };
}
