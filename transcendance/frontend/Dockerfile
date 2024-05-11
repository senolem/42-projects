FROM node:20.11-alpine as build-stage
WORKDIR /app
COPY ./ /app
RUN npm install
RUN npm run build
EXPOSE 8080

FROM nginx:alpine as production-stage
RUN mkdir /app
COPY --from=build-stage /app/dist /app
COPY nginx.conf /etc/nginx/nginx.conf