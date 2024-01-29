import { styled } from "@mui/material/styles";
import Accordion from "@mui/material/Accordion";
import AccordionSummary from "@mui/material/AccordionSummary";
import AccordionDetails from "@mui/material/AccordionDetails";

export default styled(Accordion)(({ theme, ownerState }) => {
    const { palette, functions, borders, boxShadows } = theme;
    const { bgColor, color, opacity, borderRadius, shadow, coloredShadow } = ownerState;

    const { gradients, grey, white } = palette;
    const { linearGradient } = functions;
    const { borderRadius: radius } = borders;
    const { colored } = boxShadows;

    const greyColors = {
        "grey-100": grey[100],
        "grey-200": grey[200],
        "grey-300": grey[300],
        "grey-400": grey[400],
        "grey-500": grey[500],
        "grey-600": grey[600],
        "grey-700": grey[700],
        "grey-800": grey[800],
        "grey-900": grey[900],
    };

    const validGradients = [
        "primary",
        "secondary",
        "info",
        "success",
        "warning",
        "error",
        "dark",
        "light",
        "bgcolor",
    ];

    const validColors = [
        "transparent",
        "white",
        "black",
        "primary",
        "secondary",
        "info",
        "success",
        "warning",
        "error",
        "light",
        "dark",
        "text",
        "grey-100",
        "grey-200",
        "grey-300",
        "grey-400",
        "grey-500",
        "grey-600",
        "grey-700",
        "grey-800",
        "grey-900",
    ];

    const validBorderRadius = ["xs", "sm", "md", "lg", "xl", "xxl", "section"];
    const validBoxShadows = ["xs", "sm", "md", "lg", "xl", "xxl", "inset"];

    // background value
    let backgroundValue = bgColor;

    if (validGradients.find((el) => el === bgColor)) {
        backgroundValue = linearGradient(gradients[bgColor].main, gradients[bgColor].state);
    } else if (validColors.find((el) => el === bgColor)) {
        backgroundValue = palette[bgColor] ? palette[bgColor].main : greyColors[bgColor];
    }

    // color value
    let colorValue = color;

    if (validColors.find((el) => el === color)) {
        colorValue = palette[color] ? palette[color].main : greyColors[color];
    }

    // borderRadius value
    let borderRadiusValue = borderRadius;

    if (validBorderRadius.find((el) => el === borderRadius)) {
        borderRadiusValue = radius[borderRadius];
    }

    // boxShadow value
    let boxShadowValue = "none";

    if (validBoxShadows.find((el) => el === shadow)) {
        boxShadowValue = boxShadows[shadow];
    } else if (coloredShadow) {
        boxShadowValue = colored[coloredShadow] ? colored[coloredShadow] : "none";
    }

    return {
        opacity,
        background: backgroundValue,
        color: colorValue,
        borderRadius: borderRadiusValue,
        boxShadow: boxShadowValue,
    };
});

