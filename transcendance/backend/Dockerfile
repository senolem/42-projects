FROM node:20.11-alpine as build-stage
WORKDIR /app
COPY . /app
RUN npm install
RUN npm run build
EXPOSE 3000
EXPOSE 3001
CMD ["npm", "run", "start:prod"]