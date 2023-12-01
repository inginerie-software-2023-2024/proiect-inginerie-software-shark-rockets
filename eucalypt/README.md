**Documentation built by Developers**

Each element is well presented in very complex documentation.

You can read more about the [documentation here](https://material-dashboard-react-node-docs.creative-tim.com/react/login/material-dashboard-node/).

**HELPFUL LINKS**

- View [Github Repository](https://github.com/creativetimofficial/material-dashboard-react-nodejs)
- Check [FAQ Page](https://www.creative-tim.com/faq)

## Quick start

## Prerequisites

For your local development you need to have `Node.js` and `npm` version 16 or above installed and a registered MongoDB collection.

After that open a terminal in the eucalypt folder.

## ExpressJS API Backend Installation

Go to the node-api folder `cd node-api`.

To install the project you need to have version 16 of Node.js and npm version 8. The first step is to run `npm install` command. Next you need to rename the `.env.example` to `.env`. There are the variables for the database and the URLs:
- DB_LINK="mongodb-link-to-connect"

- JWT_SECRET="token"

- APP_URL_CLIENT= http://localhost:3000
- APP_URL_API= http://localhost:8080

## Material React Frontend Installation

Go to the material-react-app folder `cd ../material-react-app`.

1. Run `yarn install` or `npm install` to install our local dependencies.
2. Rename the `.env.example` to `.env`.
 - `REACT_APP_API_URL=http://localhost:8080`
 - `REACT_APP_URL=http://localhost:3000`
 - `REACT_APP_IS_DEMO=false` if you don't want any restrictions and true if you want
3. In `package.json` set the `proxy` variable to `"http://localhost:8080"`
4. Run `yarn start` or `npm start`

## Documentation

The documentation for the Material Dashboard is hosted at our [website](https://material-dashboard-react-node-docs.creative-tim.com/react/overview/material-dashboard-node/?ref=readme-mdpr).

The documentation for the ExpressJS API is hosted [here](https://documenter.getpostman.com/view/8138626/Uze1virp).

## Browser Support

At present, we officially aim to support the last two versions of the following browsers:

<img src="https://s3.amazonaws.com/creativetim_bucket/github/browser/chrome.png" width="64" height="64"> <img src="https://s3.amazonaws.com/creativetim_bucket/github/browser/firefox.png" width="64" height="64"> <img src="https://s3.amazonaws.com/creativetim_bucket/github/browser/edge.png" width="64" height="64"> <img src="https://s3.amazonaws.com/creativetim_bucket/github/browser/safari.png" width="64" height="64"> <img src="https://s3.amazonaws.com/creativetim_bucket/github/browser/opera.png" width="64" height="64">

## Licensing

- Copyright 2021 [Creative Tim](https://www.creative-tim.com?ref=readme-mdr)
- Creative Tim [license](https://www.creative-tim.com/license?ref=readme-mdr)

## Credits

- [Creative Tim](https://creative-tim.com/?ref=mdl-readme)
- [UPDIVISION](https://updivision.com)
