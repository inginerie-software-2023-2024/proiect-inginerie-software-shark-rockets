import { forwardRef } from "react";
import PropTypes from "prop-types";
import MDAccordionRoot from "components/MDAccordion/MDAccordionRoot";
import AccordionSummary from "@mui/material/AccordionSummary";
import AccordionDetails from "@mui/material/AccordionDetails";

const MDAccordion = forwardRef(
    ({ variant, bgColor, color, opacity, borderRadius, shadow, coloredShadow, ...rest }, ref) => (
        <MDAccordionRoot
            {...rest}
            ref={ref}
            ownerState={{ variant, bgColor, color, opacity, borderRadius, shadow, coloredShadow }}
        />
    )
);

MDAccordion.Summary = forwardRef(({ ...rest }, ref) => (
    <AccordionSummary {...rest} ref={ref} />
));

MDAccordion.Details = forwardRef(({ ...rest }, ref) => (
    <AccordionDetails {...rest} ref={ref} />
));

MDAccordion.defaultProps = {
    bgColor: "transparent",
    color: "dark",
    opacity: 1,
    borderRadius: "none",
    shadow: "none",
    coloredShadow: "none",
};

MDAccordion.propTypes = {
    bgColor: PropTypes.string,
    color: PropTypes.string,
    opacity: PropTypes.number,
    borderRadius: PropTypes.string,
    shadow: PropTypes.string,
    coloredShadow: PropTypes.oneOf([
        "primary",
        "secondary",
        "info",
        "success",
        "warning",
        "error",
        "light",
        "dark",
        "none",
    ]),
};

export default MDAccordion;
