FROM node:18.19.0-slim

WORKDIR /app

COPY package.json .
COPY package-lock.json .
RUN npm install

COPY . .
RUN mv compose.env .env

EXPOSE 8080
CMD ["npm", "run", "start:dev"]
