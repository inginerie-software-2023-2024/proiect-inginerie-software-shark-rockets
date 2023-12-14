import { Navigate } from "react-router-dom";

const AdminRoute = ({ isAdmin, redirectPath = "/dashboard", children }) => {

  if (!isAdmin) {
    return <Navigate to={redirectPath} replace />;
  }

  return children;
};

export default AdminRoute;
